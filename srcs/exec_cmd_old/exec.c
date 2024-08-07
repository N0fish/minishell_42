/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:40 by algultse          #+#    #+#             */
/*   Updated: 2024/08/07 23:25:01 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


pid_t	exec_child(t_data *data, t_fds fds, t_cmd *cmd, char **envp)
{
	pid_t		child;

	(void) data;
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

	// parsed->pipex = NULL;
	if (!data || !node)
		return ;
	// parsed->is_pid = false;
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
	if (use_builtin(data, node, fds))
		return ;
	cmd = prepare_cmd(data, node);
	if (!cmd)
		return ;
	cmd->pid = exec_child(data, fds, cmd, envp);
	// parsed->pipex = cmd;
	// parsed->is_pid = true;
	// if (data->all_parsed[i].pipex->pipes[0] != STDIN_FILENO && data->all_parsed[i].pipex->pipes[0] != -1)
	// 	close(data->all_parsed[i].pipex->pipes[0]);
	// if (data->all_parsed[i].pipex->pipes[1] != STDOUT_FILENO && data->all_parsed[i].pipex->pipes[1] != -1)
	// 	close(data->all_parsed[i].pipex->pipes[1]);
	// if (data->all_parsed[i].is_pid)
	// 	data->exec_error = wait_clean_up_is_error(data, data->all_parsed[i]);
	parsed->pipex->pipes[0] = fds.no;
	parsed->pipex->pipes[1] = fds.out;
	// data->forks++;
}

void	wait_and_clean(t_data *data, int pid, t_fds fds)
{
	if (fds.in != STDIN_FILENO && data->all_parsed[i].pipex->pipes[0] != -1)
		close(data->all_parsed[i].pipex->pipes[0]);
	if (data->all_parsed[i].pipex->pipes[1] != STDOUT_FILENO && data->all_parsed[i].pipex->pipes[1] != -1)
		close(data->all_parsed[i].pipex->pipes[1]);
	if (data->all_parsed[i].is_pid)
		data->exec_error = wait_clean_up_is_error(data, data->all_parsed[i]);
}

int	exec_2_plus(t_data *data, cmd_node **node, int pipe_fds[2], t_fds *fds)
{
	char	**envp;
	int		i;

	data->forks = 0;
	i = 1;
	envp = transform_envp(data->m, data->envp);
	*fds = init_fds(pipe_fds, in_out(data, (*node)->left));
	if (!fds_ok(*fds))
		return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
	trigger_cmd(data, (*node)->left, *fds, envp);
	*node = (*node)->right;
	while (*node && (*node)->type != NODE_PIPE)
	{
		*fds = update_fds(*fds, pipe_fds, \
			in_out(data, (*node)->right));
		if (!fds_ok(*fds))
			return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
		trigger_cmd(data, (*node)->left, *fds, envp);
		i++;
		*node = (*node)->right;
	}
	return (ft_free_array(data->m, (void **)envp), EXIT_SUCCESS);
}

int	exec_cmds(t_data *data, cmd_node *node)
{
	int			pipe_fds[2];
	char		**envp;
	cmd_node	*start;

	start = node;
	data->forks = 0;
	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	if (!data || !node)
		return (EXIT_FAILURE);
	if (node->type == NODE_PIPE)
		if (exec_2_plus(data, &node, pipe_fds, &data->fds) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	envp = transform_envp(data->m, data->envp);
	data->fds = end_update_fds(pipe_fds, in_out(data, node));
	if (!fds_ok(data->fds))
		return (EXIT_FAILURE);
	trigger_cmd(data, &node, data->fds, envp);
	if (pipe_fds[0] != -1)
		close(pipe_fds[0]);
	// printf("exit_code: %d\n", data->exit_code);
	wait_clean_up(data->fds, data);
	// printf("exit_code: %d\n", data->exit_code);
	ft_free_array(data->m, (void **)envp);
	return (data->exit_code);
}
