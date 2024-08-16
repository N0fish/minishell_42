#include "minishell.h"
#include "expander.h"

int	*g_status;

cmd_node	*get_command(t_data *data, char *line)
{
	cmd_node	*cmd;
	t_token		*token;

	token = lexer(data, line);
	if (!token)
		return (NULL);
	print_tokens(token);
	cmd = parser(&token);
	//cmd = expander(data, cmd);
	printf("\n!!!!show_cmd_tree!!!!\n");
	show_cmd_tree(cmd);
	printf("\n!!!!end_cmd_tree!!!!\n");
	exec_entry(data, cmd);
	//cmd_delete(cmd);
	data->entry_node = NULL;
	// executor(cmd);
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
		signals(&(data->exit_code));
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
	//rl_clear_history(); // Не компилирует с ним на mac из-за этого закоментирован
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 1)
		return (write(2, "No arguments needed\n", 20), EXIT_FAILURE);
	data = init_builtins(argv, envp);
	prompt(data);
	// exit_builtin(data, NULL, false);
	return (*g_status);
}
