/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:25 by algultse          #+#    #+#             */
/*   Updated: 2024/08/22 20:11:40 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strerror_q(t_data *data, char *name, char *text, char *err)
{
	if (data)
		write (STDERR_FILENO, data->shell_name, ft_strlen(data->shell_name));
	if (name)
	{
		write (STDERR_FILENO, ": ", 2);
		write (STDERR_FILENO, name, ft_strlen(name));
	}
	if (text)
	{
		write (STDERR_FILENO, ": ", 3);
		write (STDERR_FILENO, "`", 1);
		write (STDERR_FILENO, text, ft_strlen(text));
		write (STDERR_FILENO, "'", 1);
	}
	if (err)
	{
		write (STDERR_FILENO, ": ", 2);
		write (STDERR_FILENO, err, ft_strlen(err));
	}
	if (data || name || text || err)
		write (STDERR_FILENO, "\n", 1);
}

void	ft_strerror(t_data *data, char *name, char *text, char *err)
{
	if (data)
	{
		write (STDERR_FILENO, data->shell_name, ft_strlen(data->shell_name));
		write (STDERR_FILENO, ": ", 2);
	}
	if (name)
	{
		write (STDERR_FILENO, name, ft_strlen(name));
		write (STDERR_FILENO, ": ", 2);
	}
	if (text)
	{
		write (STDERR_FILENO, text, ft_strlen(text));
		write (STDERR_FILENO, ": ", 2);
	}
	if (err)
	{
		write (STDERR_FILENO, err, ft_strlen(err));
		write (STDERR_FILENO, "\n", 1);
	}
}

void	handle_access_errors(t_data *data, t_cmd *cmd)
{
	if (errno == EACCES)
	{
		data->exit_code = ERROR_CMD_NOT_EXET;
		ft_strerror(data, cmd->cmd, NULL, PERM_DENIED);
		return ;
	}
	data->exit_code = EX_NOTFOUND;
	if (try_dir_or_file(cmd->cmd))
		ft_strerror(data, cmd->cmd, NULL, NO_FILE_DIR);
	else
		ft_strerror(data, cmd->cmd, NULL, CMD_NOT_FOUND);
}

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

void	display_error(t_data *data, char *lim)
{
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(data->shell_name, 2);
	ft_putstr_fd(": warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("')\n", 2);
}
