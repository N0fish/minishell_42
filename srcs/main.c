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
	cmd = parser(data, &token);
	if (!cmd)
		return (NULL);
	cmd = expander(data, cmd);
	printf("\n!!!!show_cmd_tree!!!!\n");
	show_cmd_tree(cmd);
	printf("\n!!!!end_cmd_tree!!!!\n");
	exec_entry(data, cmd);
	//cmd_delete(cmd);
	data->entry_node = NULL;
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
	// rl_clear_history(); // Не компилирует с ним на mac из-за этого закоментирован
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	// t_sig	act;
	// t_sig	act_q;

	if (argc != 1)
		return (write(2, "No arguments needed\n", 20), EXIT_FAILURE);
    // act.sa_handler = &handler_sigint; 
    // act.sa_flags = 0;
	// sigemptyset(&act.sa_mask);
	// sigaddset(&act.sa_mask, CNTRL_C);
    // sigaction(CNTRL_C, &act, NULL);

    // act_q.sa_handler = SIG_IGN; 
    // act_q.sa_flags = SA_RESTART;
	// sigemptyset(&act_q.sa_mask);
	// sigaddset(&act_q.sa_mask, CNTRL_B_SLASH);
    // sigaction(CNTRL_B_SLASH, &act_q, NULL);
	data = init_builtins(argv, envp);
	prompt(data);
	// exit_builtin(data, NULL, false);
	return (*g_status);
}
