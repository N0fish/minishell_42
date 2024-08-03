/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:01:55 by algultse          #+#    #+#             */
/*   Updated: 2024/07/22 12:01:56 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_write(t_data *data, char *name, char *arg, int fd)
{
	ssize_t	res_wrt;

	res_wrt = write(fd, arg, ft_strlen(arg));
	if (res_wrt < 0)
	{
		if (errno == ENOSPC)
			ft_strerror(data, name, "write error", "No space left on device");
		else
			ft_strerror(data, name, "write error", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
