/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:25 by algultse          #+#    #+#             */
/*   Updated: 2024/07/29 11:59:04 by algultse         ###   ########.fr       */
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
		write (STDERR_FILENO, "'", 1);
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
