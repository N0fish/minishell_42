#include "minishell.h"

cmd_node	*get_command(t_data *data, char *line)
{
	cmd_node	*cmd;
	t_token		*token;

	token = lexer(line);
	//print_tokens(token);
	cmd = parser(&token);
	// printf("\n!!!!show_cmd_tree!!!!\n");
	// show_cmd_tree(cmd);
	// printf("\n!!!!end_cmd_tree!!!!\n");
	exec_entry(data, cmd);
	cmd_delete(cmd);
	data->entry_node = NULL;
	// executor(cmd);
	if (token)
		free(token);
	return (cmd);
}

bool	ft_isempty(const char *str)
{
	while (*str != '\0')
	{
		if (!(*str >= '\t' && *str <= '\r') && *str != ' ')
			return (false);
		str++;
	}
	return (true);
}

void	prompt(t_data *data)
{
	char	*line;

	while (true)
	{
		line = NULL;
		line = readline(MISS_PROMPT);
		if (line == NULL)
			exit_builtin(data, NULL, false);
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
	rl_clear_history(); // Не компилирует с ним на mac из-за этого закоментирован
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		(printf("No arguments needed\n"), exit(EXIT_FAILURE));
	// signals
	data = init_builtins(argv, envp);
	prompt(data);
	// exit_builtin(data, NULL, false);
	return (EXIT_SUCCESS);
}
