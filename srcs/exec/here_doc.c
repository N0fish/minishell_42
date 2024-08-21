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

char	*process_key(t_data *data, char *line, \
					int len_key[2], int *diff)
{
	char	*key;
	char	*value;
	char	*res_str;

	if (!data || !line)
		return (NULL);
	key = seek_key_in_str(data, line, len_key);
	value = seek_env_or_exit_code(data, key);
	ft_free(data->m, key);
	if (!value)
		return (NULL);
	res_str = replace_key_to_value(line, len_key, value);
	if (res_str)
	{
		free(line);
		line = res_str;
		*diff = len_key[0] + ft_strlen(value) - 1;
		ft_free(data->m, value);
	}
	return (line);
}

int	*find_key_pos(char *str, int *len, int i)
{
	len[0] = -1;
	len[1] = -1;
	if (!str || i >= (int)ft_strlen(str))
		return (NULL);
	while (str[i] != '\0' && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (NULL);
	len[0] = i;
	while (str[i] != '\0' && str[i + 1] != '\0' \
		&& str[i + 1] != '$' && str[i] != '?' \
		&& (str[i + 1] != ' ' && !(str[i + 1] >= '\t' && str[i + 1] <= '\r')))
		i++;
	len[1] = i;
	if (len[0] == len[1])
		return (NULL);
	return (len);
}

int	heredoc_loop(t_data *data, char **line, int pipe_fds[2])
{
	*line = is_there_env(data, *line);
	if (!*line)
		ft_putstr_fd("", pipe_fds[1]);
	else
		ft_putstr_fd(*line, pipe_fds[1]);
	ft_putstr_fd("\n", pipe_fds[1]);
	if (*line)
		free(*line);
	*line = readline("> ");
	// if (!*line)
	// 	return (EXIT_FAILURE);
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
