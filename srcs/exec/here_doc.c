/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:28 by algultse          #+#    #+#             */
/*   Updated: 2024/07/16 13:23:42 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(t_data *data, char *lim)
{
	ft_putchar_fd('\n', 2);
	ft_putstr_fd(data->shell_name, 2);
	ft_putstr_fd(": warning: here-document delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted `", 2);
	ft_putstr_fd(lim, 2);
	ft_putstr_fd("')\n", 2);
}

char	*is_there_env(t_data *data, char *line);

// char	*is_there_env(t_data *data, char *line)
// {
// 	char	*start_line;
// 	char	*save_line;
// 	int		len_key[2];
// 	int		offset;

// 	if (!data || !line)
// 		return (NULL);
// 	start_line = line;
// 	save_line = start_line;
// 	while (*start_line != '\0')
// 	{
// 		offset = start_line - save_line;
// 		ft_printf("offset: %d, start_line: %s\n", offset, start_line);
// 		find_key_pos(line, len_key, offset);
// 		save_line = start_line;
// 		if (len_key[0] == -1 || len_key[1] == -1)
// 			break ;
// 		if (len_key[0] == len_key[1])
// 		{
// 			start_line++;
// 			continue ;
// 		}
// 		line = process_key(data, line, len_key, &start_line);
// 	}
// 	return (line);
// }

int	heredoc_loop(t_data *data, char **line, int pipe_fds[2])
{
	*line = is_there_env(data, *line);
	if (!*line)
		return (EXIT_FAILURE);
	ft_putstr_fd(*line, pipe_fds[1]);
	ft_putstr_fd("\n", pipe_fds[1]);
	if (*line)
		free(*line);
	*line = readline("> ");
	if (!*line)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	heredoc_fork(t_data *data, int pipe_fds[2], char *limiter)
{
	char	*line;

	g_status = &data->exit_code;
	heredoc_child_signal();
	line = readline("> ");
	while (line)
	{
		if (ft_strlen(line) >= 1 \
			&& ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			free(line);
			data->exit_code = EXIT_SUCCESS;
			return (close(pipe_fds[1]), exit_builtin(data, NULL, false), true);
		}
		if (heredoc_loop(data, &line, pipe_fds) == EXIT_FAILURE)
		{
			data->exit_code = EXIT_SUCCESS;
			return (close(pipe_fds[1]), exit_builtin(data, NULL, false), true);
		}
	}
	display_error(data, limiter);
	data->exit_code = EXIT_FAILURE;
	return (close(pipe_fds[1]), exit_builtin(data, NULL, false), false);
}

int	handle_heredoc(t_data *data, char *limiter)
{
	int	pipe_fds[2];
	int	status;
	int	pid;

	pipe(pipe_fds);
	pid = fork();
	if (pid < 0)
	{
		data->exit_code = -1;
		return (ft_strerror(data, "fork", NULL, strerror(errno)), false);
	}
	if (pid == 0)
	{
		close(pipe_fds[0]);
		heredoc_fork(data, pipe_fds, limiter);
	}
	heredoc_parent_signal();
	close(pipe_fds[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		data->exit_code = WEXITSTATUS(status);
		return (close(pipe_fds[0]), -2);
	}
	return (pipe_fds[0]);
}
