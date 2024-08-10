/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:40 by algultse          #+#    #+#             */
/*   Updated: 2024/08/09 23:30:11 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_cmd(t_data *data, cmd_node *node, t_fds fds, char **envp)
{
	t_cmd	*cmd;
	pid_t	pid;

	if (!data || !node)
		return ;
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
		return ;
	cmd = prepare_cmd(data, node);
	if (!cmd)
		return ;
	pid = exec_child(data, fds, cmd, envp);
	data->exec_error = waitpid(pid, &data->wtpd, 0) == -1;
	close_fds(fds);
	free_cmd(data, cmd);
}

int	exec_2_plus(t_data *data, cmd_node **node, t_fds *fds, char **envp)
{
	*fds = init_fds(in_out(data, (*node)->left));
	if (!fds_ok(*fds))
		return (EXIT_FAILURE);
	fork_cmd(data, (*node)->left, *fds, envp);
	*node = (*node)->right;
	while (*node && (*node)->type == NODE_PIPE)
	{
		*fds = update_fds(*fds, in_out(data, (*node)->left));
		if (!fds_ok(*fds))
			return (EXIT_FAILURE);
		fork_cmd(data, (*node)->left, *fds, envp);
		*node = (*node)->right;
	}
	return (EXIT_SUCCESS);
}

int	exec_cmds(t_data *data, cmd_node *node)
{
	char	**envp;
	t_fds	fds;

	if (!data || !node)
		return (EXIT_FAILURE);
	envp = transform_envp(data->m, data->envp);
	if (exec_2_plus(data, &node, &fds, envp) == EXIT_FAILURE)
		return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
	fds = end_update_fds(fds, in_out(data, node));
	if (!fds_ok(fds))
		return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
	fork_cmd(data, node, fds, envp);
	data->exit_code = update_exit_code(data);
	ft_free_array(data->m, (void **)envp);
	return (data->exit_code);
}

int	exec_cmd(t_data *data, cmd_node *node)
{
	t_fds	fds;
	char	**envp;

	if (!data || !node)
		return (EXIT_FAILURE);
	fds = in_out(data, node);
	if (!fds_ok(fds))
		return (EXIT_FAILURE);
	if (is_redirect_node(node))
		node = node->left;
	if (use_builtin(data, node, fds, true))
		return (data->exit_code);
	envp = transform_envp(data->m, data->envp);
	fork_cmd(data, node, fds, envp);
	data->exit_code = update_exit_code(data);
	return (data->exit_code);
}

int	exec_entry(t_data *data, cmd_node *node)
{
	if (!data || !node)
		return (EXIT_FAILURE);
	data->exec_error = false;
	if (node->type == NODE_PIPE)
		exec_cmds(data, node);
	else
		exec_cmd(data, node);
	return (data->exit_code);
}
