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
				ft_strerror(data, NULL, cmd->cmd, "command not found");
			}
			else
				execve(cmd->cmd, cmd->args, envp);
		}
		exit_builtin(data, NULL, false);
	}
	return (child);
}
