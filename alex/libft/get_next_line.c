/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:42:24 by algultse          #+#    #+#             */
/*   Updated: 2024/04/08 11:50:24 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_save(char **save, char **line, size_t *len_n, char **tmp)
{
	while ((*save)[*len_n] != '\n')
		(*len_n)++;
	if ((*save)[*len_n] == '\n')
		(*len_n)++;
	*line = ft_substr(*save, 0, *len_n);
	if (!*line)
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	*tmp = NULL;
	if ((ft_strlen(*save) - *len_n) >= 1)
	{
		*tmp = ft_substr(*save, *len_n, ft_strlen(*save) - *len_n);
		if (!*tmp)
		{
			free(*save);
			*save = NULL;
			return (NULL);
		}
	}
	return (*save);
}

static char	*get_line(char **save, ssize_t bytes_read)
{
	char	*line;
	size_t	len_n;
	char	*tmp;

	if (bytes_read < 0 || !*save)
		return (NULL);
	if (!bytes_read && !ft_strchr(*save, '\n'))
	{
		line = ft_strdup(*save);
		free(*save);
		*save = NULL;
		return (line);
	}
	len_n = 0;
	*save = get_save(&*save, &line, &len_n, &tmp);
	if (!*save)
	{
		free (line);
		free (tmp);
		return (NULL);
	}
	free(*save);
	*save = NULL;
	*save = tmp;
	return (line);
}

static char	*read_buf(int fd, char **save, char **buf, ssize_t *bytes_read)
{
	char	*tmp;

	*bytes_read = read(fd, *buf, BUFFER_SIZE);
	if (*bytes_read == -1)
	{
		free(*buf);
		*buf = NULL;
		return (NULL);
	}
	(*buf)[*bytes_read] = '\0';
	if (*bytes_read != 0)
	{
		if (!*save)
			tmp = ft_strdup(*buf);
		else
		{
			tmp = ft_strjoin(*save, *buf);
			free(*save);
			*save = NULL;
		}
		*save = tmp;
	}
	return (*save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	ssize_t		bytes_read;

	if (fd == FREE_STATIC_FD && save)
		free(save);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		save = read_buf(fd, &save, &buf, &bytes_read);
		if (!save)
		{
			free(buf);
			return (NULL);
		}
		if (ft_strchr(save, '\n'))
			break ;
	}
	free(buf);
	return (get_line(&save, bytes_read));
}	
