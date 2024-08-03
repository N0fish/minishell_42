/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:25:25 by algultse          #+#    #+#             */
/*   Updated: 2024/07/22 12:25:19 by algultse         ###   ########.fr       */
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

int	wait_clean_up_is_error(t_data *data, t_parsed parsed)
{
	return ((parsed.pipex->pid > -1 \
			&& waitpid(parsed.pipex->pid, &data->wtpd, 0) == -1) \
			|| parsed.pipex->pid == -1);
}

void	wait_clean_up(t_fds io, t_data *data)
{
	int i;

	i = 0;
	data->exec_error = false;
	if (data && data->all_parsed)
	{
		while (data->forks > 0)
		{
			if (data->all_parsed[i].pipex->pipes[0] != STDIN_FILENO && data->all_parsed[i].pipex->pipes[0] != -1)
				close(data->all_parsed[i].pipex->pipes[0]);
			if (data->all_parsed[i].pipex->pipes[1] != STDOUT_FILENO && data->all_parsed[i].pipex->pipes[1] != -1)
				close(data->all_parsed[i].pipex->pipes[1]);
			if (data->all_parsed[i].is_pid)
				data->exec_error = wait_clean_up_is_error(data, data->all_parsed[i]);
			data->forks--;
			i++;
		}
	}
	if (io.in != STDIN_FILENO && io.in != -1)
		close(io.in);
	if (io.out != STDOUT_FILENO && io.out != -1)
		close(io.out);
	data->exit_code = update_exit_code(data);
}
