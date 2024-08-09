/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:55 by algultse          #+#    #+#             */
/*   Updated: 2024/08/09 21:28:45 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	fds_ok(t_fds fds)
{
	return (fds.in != -1 && fds.out != -1);
}

int	find_final_fd(t_data *data, cmd_node *node, \
						int node_type, int open_modes[2])
{
	int	fd;

	if (!data || !node)
		return (-1);
	while (node && node->type == node_type)
	{
		fd = open(node->data, open_modes[0], open_modes[1]);
		if (fd == -1)
			ft_strerror_q(data, node->data, NO_FILE_DIR, NULL);
		node = node->right;
		if (node && node->type == node_type && fd != -1)
			close(fd);
	}
	return (fd);
}

void	close_fds(t_fds fds)
{
	if (fds.in != STDIN_FILENO && fds.in != -1)
		close(fds.in);
	if (fds.out != STDOUT_FILENO && fds.out != -1)
		close(fds.out);
	if (fds.pipe[0] != STDIN_FILENO && fds.pipe[0] != -1)
		close(fds.pipe[0]);
	// fds.pipe[1] == 0
	if (fds.pipe[1] != STDOUT_FILENO && fds.pipe[1] != -1)
		close(fds.pipe[1]);
}
