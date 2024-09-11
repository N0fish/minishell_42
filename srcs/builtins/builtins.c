/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:13 by algultse          #+#    #+#             */
/*   Updated: 2024/09/11 14:16:31 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_builtins(char **argv, char **envp)
{
	t_data	*data;

	data = init(argv, envp);
	if (!data)
		exit(EXIT_FAILURE);
	return (data);
}

void	exec_builtin(t_data *data, t_cmd_node *cmd, bool exit_display)
{
	if (!data || !cmd || !cmd->data)
		return ;
	if (!ft_strcmp(cmd->data, "pwd"))
		data->exit_code = pwd_builtin(data);
	else if (!ft_strcmp(cmd->data, "cd"))
		data->exit_code = cd_builtin(data, cmd->right);
	else if (!ft_strcmp(cmd->data, "unset"))
		data->exit_code = unset_builtin(data, cmd->right);
	else if (!ft_strcmp(cmd->data, "env"))
		data->exit_code = env_builtin(data);
	else if (!ft_strcmp(cmd->data, "export"))
		data->exit_code = export_builtin(data, cmd->right);
	else if (!ft_strcmp(cmd->data, "echo"))
		data->exit_code = echo_builtin(data, cmd->right);
	else if (!ft_strcmp(cmd->data, "exit"))
		exit_builtin(data, cmd->right, exit_display);
}

bool	is_builtin(t_data *data, t_cmd_node *cmd)
{
	if (!data || !cmd || !cmd->data)
		return (false);
	return (ft_match_any(data, cmd->data, \
		"pwd,cd,unset,env,export,echo,exit"));
}

bool	use_builtin(t_data *data, t_cmd_node *cmd, t_fds fds, bool exit_display)
{
	if (!data || !cmd)
		return (false);
	if (!is_builtin(data, cmd))
		return (false);
	data->out_fd = dup(STDOUT_FILENO);
	data->in_fd = dup(STDIN_FILENO);
	if (data->out_fd < 0 || data->in_fd < 0 || \
		dup2(fds.out, STDOUT_FILENO) < 0 || \
		dup2(fds.in, STDIN_FILENO) < 0)
		return (true);
	exec_builtin(data, cmd, exit_display);
	if (dup2(data->out_fd, STDOUT_FILENO) < 0 || \
		dup2(data->in_fd, STDIN_FILENO) < 0)
		return (true);
	close(data->out_fd);
	data->out_fd = -1;
	close(data->in_fd);
	data->in_fd = -1;
	close_fds(fds);
	return (true);
}

bool	fork_builtin(t_data *data, t_cmd_node *cmd, t_fds fds, pid_t *child)
{
	if (!is_builtin(data, cmd))
		return (false);
	*child = fork();
	if (*child < 0)
	{
		ft_strerror(data, "fork", NULL, strerror(errno));
		data->exit_code = -1;
		return (false);
	}
	if (*child == 0)
	{
		dup2(fds.in, STDIN_FILENO);
		dup2(fds.out, STDOUT_FILENO);
		use_builtin(data, cmd, fds, false);
		close_child_fds(fds);
		exit_builtin(data, NULL, false);
	}
	data->exec_error = waitpid(*child, &data->wtpd, 0) == -1;
	close_fds(fds);
	return (true);
}
