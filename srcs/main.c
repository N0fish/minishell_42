#include "minishell.h"

cmd_node	*get_command(t_data *data, char *line)
{
	char		**tokens;
	cmd_node	*cmd;
	t_token		*token;

	(void)data;
	tokens = lexer(line);
	token = convert_from_tokens(tokens);
	//print_tokens(token);
	cmd = parser(&token);
	printf("\n!!!!show_cmd_tree!!!!\n");
	show_cmd_tree(cmd);
	printf("\n!!!!end_cmd_tree!!!!\n");
	// exec_cmds(data, cmd);
	exec_entry(data, cmd);
	// executor(cmd);
	free(tokens);
	free(token);
	return (cmd);
}

int	ft_isempty(char *str)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (str[++i] != '\0')
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != ' ')
			counter++;
	if (counter == 0)
		return (1);
	return (0);
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
			// ft_free_cmd(data);
			free(line);
		}
	}
	// rl_clear_history (); // Не компилирует с ним на mac из-за этого закоментирован
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data				*data;

	if (argc != 1)
		(printf("No arguments needed\n"), exit(EXIT_FAILURE));
	// signals
	(void)data;
	data = init_builtins(argv, envp);
	prompt(data);
	// exit_builtin(data, NULL, false);
	return (EXIT_SUCCESS);
}
