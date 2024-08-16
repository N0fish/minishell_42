/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:53:12 by alex              #+#    #+#             */
/*   Updated: 2024/08/16 13:33:35 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

// Я думаю следует сюда записать все что связано с builtin функциями.

/*
Структура для хранения внутренних данных команды. Сюда записываются pipes, redirect и аргументы комманды.
Можно менять по своему усмотрению. (главное не сильно усложнять :) )
*/
typedef struct cmd_internal
{
	int     argc;
	char    **argv;
	bool    stdin_pipe;
	bool    stdout_pipe;
	int     pipe_read;
	int     pipe_write;
    char    *redirect_in;
    char    *redirect_out;
}   cmd_internal;

typedef struct s_fds {
	int	in;
	int	out;
	int	no;
	int pipe[2];
}				t_fds;

typedef struct s_data
{
	struct s_malloc	*m;
	struct s_envp	*envp;
	int				exit_code;
	char			*shell_name;
	bool			here_doc;
	int				wtpd;
	bool			exec_error;
	int				out_fd;
	int				in_fd;
	struct s_fds	fds;
	struct cmd_node	*entry_node;
}				t_data;

#endif