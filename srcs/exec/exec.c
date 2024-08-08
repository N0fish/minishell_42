/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:40 by algultse          #+#    #+#             */
/*   Updated: 2024/08/08 22:46:37 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


pid_t	exec_child(t_data *data, t_fds fds, t_cmd *cmd, char **envp)
{
	pid_t		child;

	if (fds.in == -1 || fds.out == -1)
		return (-1);
	child = fork();
	if (child == 0)
	{
		data->exit_code = 0;
		dup2(fds.in, STDIN_FILENO);
		dup2(fds.out, STDOUT_FILENO);
		if (fds.no >= 0 && fds.no != fds.in && fds.no != fds.out)
			close(fds.no);
		if (is_directory(cmd->cmd, false))
		{
			data->exit_code = EX_NOTFOUND;
			ft_strerror(data, NULL, cmd->cmd, "No such file or directory");
		}
		else
		{
			if (access(cmd->cmd, X_OK) != 0)
			{
				data->exit_code = EX_NOTFOUND;
				ft_strerror(NULL, NULL, cmd->cmd, "command not found");
			}
			else
				execve(cmd->cmd, cmd->args, envp);
		}
		exit_builtin(data, NULL, false);
		// if (fds.in != STDIN_FILENO && fds.in != -1)
		// 	close(fds.in);
		// if (fds.out != STDOUT_FILENO && fds.out != -1)
		// 	close(fds.out);
		// close(STDIN_FILENO);
		// close(STDOUT_FILENO);
	}
	return (child);
}

t_fds	trigger_cmd(t_data *data, cmd_node *node, t_fds fds, char **envp)
{
	t_cmd	*cmd;

	if (!data || !node)
		return (fds);
	// attendre alex pour << HERE_DOC
	// if (parsed->eof && *parsed->eof)
	// {
	// 	parsed->is_pid = true;
	// 	handle_heredoc(*parsed->eof, fds.out);
	// 	return ;
	// }
	if (node->type != NODE_CMDPATH)
		node = node->left;
	modif_env(data, "_", node->data);
	if (fork_builtin(data, node, fds))
		return (fds);
	cmd = prepare_cmd(data, node);
	if (!cmd)
		return (fds);
	cmd->pid = exec_child(data, fds, cmd, envp);
	printf("trigger_cmd before waitpid\n");
	data->exec_error = waitpid(cmd->pid, &data->wtpd, 0) == -1;
	printf("trigger_cmd > fds.in: %d, fds.out: %d\n", fds.in, fds.out);
	if (fds.in != STDIN_FILENO && fds.in != -1)
		close(fds.in);
	if (fds.out != STDOUT_FILENO && fds.out != -1)
		close(fds.out);
	// parsed->pipex->pipes[0] = fds.no;
	// parsed->pipex->pipes[1] = fds.out;
	// data->forks++;
	return (fds);
}

int	exec_2_plus(t_data *data, cmd_node **node, int pipe_fds[2], t_fds *fds)
{
	char	**envp;

	envp = transform_envp(data->m, data->envp);
	*fds = init_fds(pipe_fds, in_out(data, (*node)->left));
	if (!fds_ok(*fds))
		return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
	trigger_cmd(data, (*node)->left, *fds, envp);
	*node = (*node)->right;
	while (*node && (*node)->type == NODE_PIPE)
	{
		*fds = update_fds(*fds, pipe_fds, \
			in_out(data, (*node)->left));
		if (!fds_ok(*fds))
			return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
		trigger_cmd(data, (*node)->left, *fds, envp);
		*node = (*node)->right;
	}
	return (ft_free_array(data->m, (void **)envp), EXIT_SUCCESS);
}

int	exec_cmds(t_data *data, cmd_node *node)
{
	int			pipe_fds[2];
	char		**envp;
	t_fds		fds;

	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	if (!data || !node)
		return (EXIT_FAILURE);
	if (exec_2_plus(data, &node, pipe_fds, &fds) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	envp = transform_envp(data->m, data->envp);
	fds = end_update_fds(pipe_fds, in_out(data, node));
	if (!fds_ok(fds))
		return (EXIT_FAILURE);
	trigger_cmd(data, node, fds, envp);
	if (pipe_fds[0] != -1)
		close(pipe_fds[0]);
	// printf("exit_code: %d\n", data->exit_code);
	wait_clean_up(fds, data, node);
	// printf("exit_code: %d\n", data->exit_code);
	ft_free_array(data->m, (void **)envp);
	return (data->exit_code);
}

int exec_cmd(t_data *data, cmd_node *node)
{
	t_fds 	fds;
	char	**envp;

	fds = in_out(data, node);
	if (is_redirect_node(node))
		node = node->left;
	if (use_builtin(data, node, fds))
		return (data->exit_code);
	envp = transform_envp(data->m, data->envp);
	if (!fds_ok(fds))
		return (EXIT_FAILURE);
	trigger_cmd(data, node, fds, envp);
	return (data->exit_code);
}

int	exec_entry(t_data *data, cmd_node *node)
{
	if (node->type == NODE_PIPE)
		exec_cmds(data, node);
	else
		exec_cmd(data, node);
	return (data->exit_code);
}
