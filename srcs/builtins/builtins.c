/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:13 by algultse          #+#    #+#             */
/*   Updated: 2024/07/22 12:26:45 by algultse         ###   ########.fr       */
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

void	exec_builtin(t_data *data, t_parsed *parsed)
{
	if (!data || !parsed || !parsed->cmd)
		return ;
	parsed->pipex = NULL;
	if (!ft_strcmp(parsed->cmd[0], "pwd"))
		data->exit_code = pwd_builtin(data);
	else if (!ft_strcmp(parsed->cmd[0], "cd"))
		data->exit_code = cd_builtin(data, parsed->cmd[1], parsed->cmd);
	else if (!ft_strcmp(parsed->cmd[0], "unset"))
		data->exit_code = unset_builtin(data, parsed->cmd[1]);
	else if (!ft_strcmp(parsed->cmd[0], "env"))
		data->exit_code = env_builtin(data);
	else if (!ft_strcmp(parsed->cmd[0], "export"))
		data->exit_code = export_builtin(data, parsed->cmd);
	else if (!ft_strcmp(parsed->cmd[0], "echo"))
		data->exit_code = echo_builtin(data, parsed->cmd);
	else if (!ft_strcmp(parsed->cmd[0], "exit"))
		exit_builtin(data, parsed->cmd, true);
}

pid_t	exec_or_fork_builtin(t_data *data, t_fds fds, t_parsed *parsed)
{
	pid_t	child;

	parsed->is_pid = false;
	if (data->nb_cmds < 2)
		return (exec_builtin(data, parsed), -1);
	if (fds.in == -1 || fds.out == -1)
	{
		data->exit_code = -1;
		return (-1);
	}
	parsed->is_pid = true;
	data->forks++;
	child = fork();
	if (child < 0)
	{
		ft_strerror(data, "fork", NULL, strerror(errno));
		data->exit_code = -1;
		return (-1);
	}
	if (child == 0)
	{
		dup2(fds.in, STDIN_FILENO);
		dup2(fds.out, STDOUT_FILENO);
		exec_builtin(data, parsed);
		if (fds.no != -1 && fds.no != fds.in && fds.no != fds.out)
			close(fds.no);
		exit_builtin(data, NULL, false);
	}
	return (child);
}

bool	use_builtin_close(t_data *data)
{
	if (!data)
		return (false);
	if (data->out_fd != -1)
	{
		close(data->out_fd);
		data->out_fd = -1;
	}
	if (data->in_fd != -1)
	{
		close(data->in_fd);
		data->in_fd = -1;
	}
	return (true);
}

bool	use_builtin(t_data *data, t_parsed *parsed, t_fds fds)
{
	if (!data || !parsed || !parsed->cmd || !parsed->cmd[0])
		return (false);
	if (!ft_match_any(data, parsed->cmd[0], \
		"pwd,cd,unset,env,export,echo,exit"))
		return (false);
	data->out_fd = dup(STDOUT_FILENO);
	data->in_fd = dup(STDIN_FILENO);
	if (data->out_fd < 0 || data->in_fd < 0 || \
		dup2(fds.out, STDOUT_FILENO) < 0 || \
		dup2(fds.in, STDIN_FILENO) < 0)
		return (true);
	parsed->pipex = pid_only_cmd(data->m, \
		exec_or_fork_builtin(data, fds, parsed));
	if (dup2(data->out_fd, STDOUT_FILENO) < 0 || \
		dup2(data->in_fd, STDIN_FILENO) < 0)
		return (true);
	return (use_builtin_close(data));
}
