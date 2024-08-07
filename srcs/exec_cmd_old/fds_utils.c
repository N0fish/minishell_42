/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:55 by algultse          #+#    #+#             */
/*   Updated: 2024/07/16 13:21:56 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_to_fd(t_data *data, char *path, bool chev_left, bool right_append)
{
	int	fd;
	int	right_mode;

	right_mode = O_CREAT | O_WRONLY | O_TRUNC;
	if (right_append)
		right_mode = O_CREAT | O_WRONLY | O_APPEND;
	if (!path)
		return (FREE_STATIC_FD);
	if (*path == '0')
		return (STDIN_FILENO);
	if (*path == '1')
		return (STDOUT_FILENO);
	if (*path == '2')
		return (STDERR_FILENO);
	if (chev_left)
		fd = open(path, O_RDONLY);
	else
		fd = open(path, right_mode, 0644);
	if (fd == -1)
		ft_strerror_q(data, path, NO_FILE_DIR, NULL);
	return (fd);
}

bool	fds_ok(t_fds fds)
{
	return (fds.in != -1 && fds.out != -1);
}
