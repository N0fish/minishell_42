/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:22:11 by algultse          #+#    #+#             */
/*   Updated: 2024/08/09 23:24:05 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	init_fds(t_fds io)
{
	int	pipe_res;
	int	out_fd;
	int	pipe_fds[2];

	pipe_res = pipe(pipe_fds);
	if (pipe_res == -1)
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1, \
			.pipe = {-1, -1}, \
		});
	out_fd = pipe_fds[1]; //A1
	if (io.out != STDOUT_FILENO)
		out_fd = io.out;
	// .in = io.in, // STDIN or L1
	// .out = out_fd, // A1
	// .no = pipe_fds[0] // A0
	return ((t_fds){\
		.in = io.in, \
		.out = out_fd, \
		.no = pipe_fds[0], \
		.pipe = {-1, pipe_fds[1]} \
	});
}

t_fds	update_fds(t_fds fds, t_fds io)
{
	int	new_pipe_fds[2];
	int	pipe_res;

	pipe_res = pipe(new_pipe_fds);
	if (pipe_res == -1)
	{
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1, \
			.pipe = {-1, -1} \
		});
	}
	// .in = A0 or L1
	fds.in = fds.no;
	if (io.in != STDIN_FILENO && io.in != -1)
		fds.in = io.in;
	// .out = B1 or R1
	fds.out = new_pipe_fds[1];
	if (io.out != STDOUT_FILENO && io.out != -1)
		fds.out = io.out;
	fds.pipe[0] = fds.no; // .pipe[0] = A0
	fds.pipe[1] = new_pipe_fds[1]; // .pipe[1] = B1
	// .no = B0
	fds.no = new_pipe_fds[0];
	return (fds);
}

t_fds	end_update_fds(t_fds fds, t_fds io)
{
	int	in_fd;

	// .in = B0
	in_fd = fds.no;
	if (io.in != STDIN_FILENO)
		in_fd = io.in;
	// .out = stdout or L1
	return ((t_fds){\
		.in = in_fd, \
		.out = io.out, \
		.no = -1, \
		.pipe = {fds.no, -1} \
	});
}

t_fds	in_out(t_data *data, cmd_node *node)
{
	int	in_fd;
	int	out_fd;
	int	open_mode[2];

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	open_mode[0] = O_CREAT | O_WRONLY | O_TRUNC;
	open_mode[1] = 0644;
	// quelle est la premiere redirect priotitaire dans node ?
	if (node && node->type == NODE_REDIRECT_OUT)
		out_fd = find_final_fd(data, node, NODE_REDIRECT_OUT, open_mode);
	open_mode[0] = O_RDONLY;
	open_mode[1] = DEFAULT_CHMOD;
	if (node && node->type == NODE_REDIRECT_IN)
		in_fd = find_final_fd(data, node, NODE_REDIRECT_IN, open_mode);
	// attendre alex pour le reste
	return ((t_fds){\
		.in = in_fd, \
		.out = out_fd, \
		.no = -1, \
		.pipe = {-1, -1} \
	});
}
