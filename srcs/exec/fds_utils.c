/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:55 by algultse          #+#    #+#             */
/*   Updated: 2024/09/11 14:13:36 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	fds_ok(t_fds fds)
{
	return (fds.in != -1 && fds.out != -1);
}

int	find_final_fd(t_data *data, t_cmd_node **red, \
						int node_type, int open_modes[2])
{
	int	fd;

	if (!data || !red || !*red)
		return (-1);
	while (*red && (*red)->type == node_type)
	{
		fd = open((*red)->data, open_modes[0], open_modes[1]);
		if (fd == -1)
		{
			data->exit_code = EXIT_FAILURE;
			ft_strerror(data, (*red)->data, NULL, NO_FILE_DIR);
			*red = (*red)->right;
			return (-1);
		}
		*red = (*red)->right;
		if (*red && (*red)->type == node_type && fd != -1)
			close(fd);
	}
	return (fd);
}

void	close_fds(t_fds fds)
{
	if (fds.in != STDIN_FILENO && fds.in != -1)
	{
		close(fds.in);
		fds.in = -1;
	}
	if (fds.out != STDOUT_FILENO && fds.out != -1)
	{
		close(fds.out);
		fds.out = -1;
	}
	if (fds.pipe[0] != STDIN_FILENO && fds.pipe[0] != -1 \
		&& fds.pipe[0] != fds.in)
	{
		close(fds.pipe[0]);
		fds.pipe[0] = -1;
	}
	if (fds.pipe[1] != STDOUT_FILENO && fds.pipe[1] != -1 \
		&& fds.pipe[1] != fds.out)
	{
		close(fds.pipe[1]);
		fds.pipe[1] = -1;
	}
}

void	close_child_fds(t_fds fds)
{
	if (fds.out >= 0 && STDOUT_FILENO != fds.out)
		close(fds.out);
	fds.out = -1;
	if (fds.no >= 0 && fds.no != fds.in && fds.no != fds.out)
	{
		close(fds.no);
		fds.no = -1;
	}
	if (fds.in >= 0 && STDIN_FILENO != fds.in)
		close(fds.in);
	fds.in = -1;
	if (fds.pipe[0] != STDIN_FILENO && fds.pipe[0] != -1 \
		&& fds.pipe[0] != fds.in)
	{
		close(fds.pipe[0]);
		fds.pipe[0] = -1;
	}
	if (fds.pipe[1] != STDOUT_FILENO && fds.pipe[1] != -1 \
		&& fds.pipe[1] != fds.out)
	{
		close(fds.pipe[1]);
		fds.pipe[1] = -1;
	}
}
