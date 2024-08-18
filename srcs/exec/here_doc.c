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

int	heredoc_loop(t_data *data, char **line, char **buf)
{
	char	*tmp;
	(void)	data;

	ft_printf("> ");
	*line = is_there_env(data, *line);
	if (!*line)
		return (EXIT_FAILURE);
	if (!*buf)
		*buf = ft_strdup_m(data->m, *line);
	else
	{
		tmp = ft_strjoin_m(data->m, *buf, *line);
		if (!tmp)
		{
			ft_free(data->m, *buf);
			free(*line);
			return (EXIT_FAILURE);
		}
		ft_free(data->m, *buf);
		*buf = tmp;
	}
	if (*line)
		free(*line);
	*line = get_next_line(STDIN_FILENO);
	if (!line)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	heredoc_fork(t_data *data, int pipe_fds[2], char *line, char *limiter)
{
	char	*buf;

	buf = NULL;
	close(pipe_fds[0]);
	while (line)
	{
		if (ft_strcmp(line, limiter) == '\n')
		{
			free(line);
			get_next_line(FREE_STATIC_FD);
			write (pipe_fds[1], buf, ft_strlen(buf));
			if (buf)
				ft_free(data->m, buf);
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
	int		pipe_fds[2];
	int		status;

	pipe(pipe_fds);
	ft_printf("> ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (-1);
	int pid = fork();
	if (pid < 0)
	{
		ft_strerror(data, "fork", NULL, strerror(errno));
		data->exit_code = -1;
		return (false);
	}
	if (pid == 0)
		heredoc_fork(data, pipe_fds, line, limiter);
	else
	{
		close(pipe_fds[1]);
		waitpid(pid, &status, 0);
	}
	return (pipe_fds[0]);
}
