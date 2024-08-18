/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:22:11 by algultse          #+#    #+#             */
/*   Updated: 2024/08/12 17:17:09 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	init_fds(t_fds io)
{
	int	pipe_res;
	int	out_fd;
	int	new_pipe_fds[2];

	pipe_res = pipe(new_pipe_fds);
	if (pipe_res == -1)
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1, \
			.pipe = {-1, -1}, \
		});
	out_fd = new_pipe_fds[1]; // A1
	if (io.out != STDOUT_FILENO)
		out_fd = io.out; // R1
	// .in = io.in, // STDIN or L1
	// .out = out_fd, // A1 or R1
	// .no = new_pipe_fds[0] // A0
	return ((t_fds){\
		.in = io.in, \
		.out = out_fd, \
		.no = new_pipe_fds[0], \
		.pipe = {-1, new_pipe_fds[1]} \
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

	// .in = A0/B0
	in_fd = fds.no;
	if (io.in != STDIN_FILENO)
		in_fd = io.in; // L1
	// .out = stdout or R1
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

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	while (node && is_redirect_node(node))
	{
		handle_redirect_out(data, &node, &out_fd);
		handle_shift_left(data, &node, &in_fd);
		handle_redirect_in(data, &node, &in_fd);
		handle_shift_right(data, &node, &out_fd);
	}

	return ((t_fds){
		.in = in_fd,
		.out = out_fd,
		.no = -1,
		.pipe = {-1, -1}
	});
}
