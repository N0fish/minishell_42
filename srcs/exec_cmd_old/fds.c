/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:22:11 by algultse          #+#    #+#             */
/*   Updated: 2024/07/22 12:25:36 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fds	init_fds(int new_pipe_fds[2], t_fds io)
{
	int	pipe_res;
	int	out_fd;

	pipe_res = pipe(new_pipe_fds);
	if (pipe_res == -1)
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1 \
		});
	out_fd = new_pipe_fds[1];
	if (io.out != STDOUT_FILENO)
	{
		// close(new_pipe_fds[1]);
		out_fd = io.out;
	}
	return ((t_fds){\
		.in = io.in, \
		.out = out_fd, \
		.no = new_pipe_fds[0] \
	});
}

t_fds	update_t_fds(t_fds fds, t_fds io, int new_pipes[2], int old_pipes[2])
{
	fds.in = old_pipes[0];
	if (io.in != STDIN_FILENO && io.in != -1)
	{
		fds.in = io.in;
		if (old_pipes[0] != -1)
			close(old_pipes[0]);
	}

	fds.out = new_pipes[1];
	if (io.out != STDOUT_FILENO && io.out != -1)
	{
		if (new_pipes[1] != -1)
			close(new_pipes[1]);
		fds.out = io.out;
	}
	fds.no = new_pipes[0];
	return (fds);
}

t_fds	update_fds(t_fds fds, int pipe_fds[2], t_fds io)
{
	int	new_pipe_fds[2];
	int	pipe_res;

	pipe_res = pipe(new_pipe_fds);
	if (!pipe_fds || pipe_res == -1)
	{
		if (fds.in != STDIN_FILENO && fds.in != -1)
			close(fds.in);
		if (pipe_fds[1] != -1)
			close(pipe_fds[1]);
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1 \
		});
	}
	if (fds.in != STDIN_FILENO && fds.in != -1)
		close(fds.in);
	if (fds.out != STDOUT_FILENO && fds.out != -1)
		close(fds.out);
	fds = update_t_fds(fds, io, new_pipe_fds, pipe_fds);
	if (pipe_fds[1] != -1)
		close(pipe_fds[1]);
	pipe_fds[0] = new_pipe_fds[0];
	pipe_fds[1] = new_pipe_fds[1];
	return (fds);
}

t_fds	end_update_fds(int pipe_fds[2], t_fds io)
{
	int	in_fd;

	if (!pipe_fds)
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1 \
		});
	if (pipe_fds[1] != -1)
		close (pipe_fds[1]);
	in_fd = io.in;
	if (io.in == STDIN_FILENO && pipe_fds[0] != -1)
		in_fd = pipe_fds[0];
	return ((t_fds){\
		.in = in_fd, \
		.out = io.out, \
		.no = pipe_fds[1] \
	});
}

t_fds	in_out(t_data *data, t_parsed parsed)
{
	if (parsed.err_code != EXIT_SUCCESS)
	{
		ft_strerror_q(data, parsed.err_msg, NULL, NULL);
		return ((t_fds){\
			.in = -1, \
			.out = -1, \
			.no = -1 \
		});
	}
	return ((t_fds){\
		.in = path_to_fd(data, parsed.entry, *parsed.entry != '0', false), \
		.out = path_to_fd(data, parsed.exit, false, parsed.ex_append), \
		.no = -1 \
	});
}
