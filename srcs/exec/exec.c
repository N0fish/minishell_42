/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:40 by algultse          #+#    #+#             */
/*   Updated: 2024/09/11 14:02:06 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	fork_cmd(t_data *data, t_cmd_node *node, t_fds fds, char **envp)
{
	t_cmd	*cmd;
	pid_t	pid;

	if (!data || !node)
		return (-1);
	if (node->type != NODE_CMDPATH)
		node = node->left;
	modif_env(data, "_", node->data);
	parent_signals();
	if (fork_builtin(data, node, fds, &pid))
		return (-1);
	cmd = prepare_cmd(data, node);
	if (!cmd)
	{
		close_fds(fds);
		return (-1);
	}
	pid = exec_child(data, fds, cmd, envp);
	close_fds(fds);
	free_cmd(data, cmd);
	return (pid);
}

int	exec_2_plus(t_data *data, t_cmd_node **node, t_fds *fds, t_ms_pids *pids)
{
	char	**envp;

	envp = transform_envp(data->m, data->envp);
	*fds = init_fds(in_out(data, (*node)->left));
	add_pid(pids, fork_cmd(data, (*node)->left, *fds, envp));
	*node = (*node)->right;
	while (*node && (*node)->type == NODE_PIPE)
	{
		*fds = update_fds(*fds, in_out(data, (*node)->left));
		if (!fds_ok(*fds))
			return (EXIT_FAILURE);
		add_pid(pids, fork_cmd(data, (*node)->left, *fds, envp));
		*node = (*node)->right;
	}
	return (EXIT_SUCCESS);
}

int	exec_cmds(t_data *data, t_cmd_node *node)
{
	char		**envp;
	t_fds		fds;
	t_ms_pids	pids;

	pids.it = -1;
	if (!data || !node)
		return (EXIT_FAILURE);
	envp = transform_envp(data->m, data->envp);
	if (exec_2_plus(data, &node, &fds, &pids) == EXIT_FAILURE)
		return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
	fds = end_update_fds(fds, in_out(data, node));
	if (!fds_ok(fds))
		return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
	add_pid(&pids, fork_cmd(data, node, fds, envp));
	wait_pids(data, pids);
	data->exit_code = update_exit_code(data);
	ft_free_array(data->m, (void **)envp);
	return (data->exit_code);
}

int	exec_cmd(t_data *data, t_cmd_node *node)
{
	t_fds		fds;
	char		**envp;
	t_ms_pids	pids;

	pids.it = -1;
	if (!data || !node)
		return (EXIT_FAILURE);
	fds = in_out(data, node);
	if (!fds_ok(fds))
		return (EXIT_FAILURE);
	if (fds.in == -2)
		return (data->exit_code);
	if (is_redirect_node(node))
		node = node->left;
	if (use_builtin(data, node, fds, true))
		return (data->exit_code);
	envp = transform_envp(data->m, data->envp);
	add_pid(&pids, fork_cmd(data, node, fds, envp));
	wait_pids(data, pids);
	data->exit_code = update_exit_code(data);
	ft_free_array(data->m, (void **)envp);
	return (data->exit_code);
}

int	exec_entry(t_data *data, t_cmd_node *node)
{
	if (!data || !node)
		return (EXIT_FAILURE);
	data->exec_error = false;
	data->entry_node = node;
	if (node->type == NODE_PIPE)
		exec_cmds(data, node);
	else
		exec_cmd(data, node);
	return (data->exit_code);
}
