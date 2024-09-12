/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:03 by algultse          #+#    #+#             */
/*   Updated: 2024/08/21 17:59:34 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*g_status;

t_cmd_node	*get_command(t_data *data, char *line)
{
	t_cmd_node	*cmd;
	t_token		*token;

	if (!data || !line)
		return (NULL);
	token = lexer(data, line);
	if (!token)
		return (NULL);
	cmd = parser(data, &token);
	if (!cmd)
		return (NULL);
	cmd = expander(data, cmd);
	if (!cmd)
		return (NULL);
	exec_entry(data, cmd);
	if (cmd)
		cmd_delete(cmd);
	data->entry_node = NULL;
	return (cmd);
}

void	prompt(t_data *data)
{
	char		*line;

	while (true)
	{
		signals(&(data->exit_code));
		line = NULL;
		line = readline(MISS_PROMPT);
		if (line == NULL)
			exit_builtin(data, NULL, true);
		else if (ft_strcmp(line, "") == 0 || ft_isempty(line))
		{
			free(line);
			continue ;
		}
		else if (ft_strlen(line) > 0)
		{
			add_history(line);
			get_command(data, line);
			free(line);
		}
	}
	rl_clear_history();
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		return (write(2, "No arguments needed\n", 20), EXIT_FAILURE);
	data = init_builtins(argv, envp);
	prompt(data);
	return (*g_status);
}
