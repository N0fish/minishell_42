/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:25:25 by algultse          #+#    #+#             */
/*   Updated: 2024/08/09 23:53:16 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_exit_code(t_data *data)
{
	if (!data)
		return (EXIT_FAILURE);
	if (data->exec_error == true)
		return (EX_NOTFOUND);
	if (data->wtpd != -1 && WIFEXITED(data->wtpd))
		return (WEXITSTATUS(data->wtpd));
	return (data->exit_code);
}

void	handle_access_errors(t_data *data, t_cmd *cmd)
{
	data->exit_code = EX_NOTFOUND;
	if (try_dir_or_file(cmd->cmd))
		ft_strerror(data, cmd->cmd, NULL, NO_FILE_DIR_CAP);
	else
		ft_strerror(data, cmd->cmd, NULL, CMD_NOT_FOUND);
}

void	exec_fork(t_data *data, t_fds fds, t_cmd *cmd, char **envp)
{
	data->exit_code = 0;
	dup2(fds.in, STDIN_FILENO);
	dup2(fds.out, STDOUT_FILENO);
	if (fds.no >= 0 && fds.no != fds.in && fds.no != fds.out)
		close(fds.no);
	if (is_directory(cmd->cmd, false))
	{
		data->exit_code = ERROR_CMD_NOT_EXET;
		ft_strerror(data, cmd->cmd, NULL, IS_A_DIR);
	}
	else
	{
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
	{
		// restore_signal();
		exec_fork(data, fds, cmd, envp);
	}
	// ignore_signal();
	return (child);
}
