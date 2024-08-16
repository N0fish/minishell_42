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
char	*check_var(t_data *data, char *str);

int	heredoc_loop(t_data *data, char **line, char **buf)
{
	char	*tmp;
	(void) data;

	ft_printf("here_doc> ");
	if (!*buf)
		*buf = ft_strdup(*line);
	else
	{
		tmp = ft_strjoin(*buf, *line);
		if (!tmp)
		{
			free(*buf);
			free(*line);
			return (EXIT_FAILURE);
		}
		free(*buf);
		*buf = tmp;
	}
	free(*line);
	*line = get_next_line(STDIN_FILENO);
	// *line = check_var(data, *line);
	return (EXIT_SUCCESS);
}

void	heredoc_fork(t_data *data, int pipe_fds[2], char *line, char *limiter, char *buf)
{
	close(pipe_fds[0]);
	while (line)
	{
		if (ft_strcmp(line, limiter) == '\n')
		{
			free(line);
			get_next_line(FREE_STATIC_FD);
			write (pipe_fds[1], buf, ft_strlen(buf));
			if (buf)
				free(buf);
			exit(EXIT_SUCCESS);
		}
		if (heredoc_loop(data, &line, &buf) == EXIT_FAILURE)
		{
			close(pipe_fds[1]);
			get_next_line(FREE_STATIC_FD);
			exit(EXIT_FAILURE);
		}
	}
}

int	handle_heredoc(t_data *data, char *limiter)
{
	char	*line;
	char	*buf;
	int		pipe_fds[2];
	int		status;

	pipe(pipe_fds);
	ft_printf("here_doc> ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (-1);
	buf = NULL;
	int pid = fork();
	if (pid == 0)
		heredoc_fork(data, pipe_fds, line, limiter, buf);
	else
	{
		close(pipe_fds[1]);
		waitpid(pid, &status, 0);
	}
	return (pipe_fds[0]);
}
