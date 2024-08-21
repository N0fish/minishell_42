/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:25:25 by algultse          #+#    #+#             */
/*   Updated: 2024/08/20 19:02:00 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_fork(t_data *data, t_fds fds, t_cmd *cmd, char **envp)
{
	data->exit_code = 0;
	dup2(fds.in, STDIN_FILENO);
	dup2(fds.out, STDOUT_FILENO);
	if (fds.no >= 0 && fds.no != fds.in && fds.no != fds.out)
		close(fds.no);
	if (!ft_strcmp(cmd->cmd, cmd->args[0]))
	{
		handle_access_errors(data, cmd);
		exit_builtin(data, NULL, false);
	}
	if (is_directory(cmd->cmd, false))
	{
		data->exit_code = ERROR_CMD_NOT_EXET;
		ft_strerror(data, cmd->cmd, NULL, IS_A_DIR);
	}
	else
	{
		child_signals();
		if (access(cmd->cmd, X_OK) != 0)
			handle_access_errors(data, cmd);
		else
			execve(cmd->cmd, cmd->args, envp);
	}
	exit_builtin(data, NULL, false);
}

pid_t	exec_child(t_data *data, t_fds fds, t_cmd *cmd, char **envp)
{
	pid_t	child;

	if (fds.in == -1 || fds.out == -1)
		return (-1);
	child = fork();
	if (child < 0)
	{
		ft_strerror(data, "fork", NULL, strerror(errno));
		data->exit_code = -1;
		return (-1);
	}
	if (child == 0)
		exec_fork(data, fds, cmd, envp);
	return (child);
}

void	add_pid(t_ms_pids *pids, pid_t pid)
{
	pids->pids[++(pids->it)] = pid;
}

void	wait_pids(t_data *data, t_ms_pids pids)
{
	int	it;

	it = -1;
	while (++it <= pids.it)
	{
		if (pids.pids[it] == -1)
			continue ;
		data->exec_error = waitpid(pids.pids[it], &data->wtpd, 0) == -1;
	}
}
