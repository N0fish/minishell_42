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

int	heredoc_loop(char **line, char **buf)
{
	char	*tmp;

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
	return (EXIT_SUCCESS);
}

int	handle_heredoc(char *limiter, int fd)
{
	char	*line;
	char	*buf;

	ft_printf("here_doc> ");
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (EXIT_FAILURE);
	buf = NULL;
	while (line)
	{
		if (ft_strcmp(line, limiter) == '\n')
		{
			free(line);
			get_next_line(FREE_STATIC_FD);
			write (fd, buf, ft_strlen(buf));
			if (buf)
				free(buf);
			return (EXIT_SUCCESS);
		}
		if (heredoc_loop(&line, &buf) == EXIT_FAILURE)
			return (get_next_line(FREE_STATIC_FD), EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}
