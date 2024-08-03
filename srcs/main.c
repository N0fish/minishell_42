#include "minishell.h"

// Функция (obtain_cmds) коллеги (оставила только её для понимания, что использовалось),
// где я забирала данные в data, чтобы использовать далее cmds.

void obtain_cmds(t_data *data, char *line)
{
	// t_parsed *all_parsed;
	char *sub_line;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;

	opened_quotes(line, 1, '\'', line);

	data->nb_cmds = count_chars(line, '|');
	data->nb_cmds++;
	data->all_parsed = (t_parsed*)malloc(sizeof(t_parsed) * (data->nb_cmds));
	data->all_parsed[0].cmd = NULL;
	data->all_parsed[0].entry = NULL;
	data->all_parsed[0].exit = NULL;
	data->all_parsed[0].ex_append = 0;
	data->all_parsed[0].eof = NULL;
	data->all_parsed[0].err_msg = NULL;
	data->all_parsed[0].err_code = 0;
	data->all_parsed[0].pipex = NULL;

	syntax_error(line, &data->all_parsed[0]);
	if (data->all_parsed[0].err_code == 2 && data->all_parsed[0].err_msg != NULL)
		data->nb_cmds = 1;
	else
	{
		if (data->all_parsed[0].eof != NULL)
		{
			while (data->all_parsed[0].eof[i] && data->all_parsed[0].eof[i] != NULL)
			{
				free(data->all_parsed[0].eof[i]);
				i++;
			}
			i = 0;
			free(data->all_parsed[0].eof);
			data->all_parsed[0].eof = NULL;
		}
		while (i < data->nb_cmds)
		{
			while (line[j] != '\0' && line[j] != '|')
			{
				if (line[j] == '\'' || line[j] == '"')
					quote_to_quote(&j, line, line[j]);
				j++;
			}
			sub_line = ft_strndup(line + k, j - k);
			parsing(&data->all_parsed[i], sub_line, data);
			j++;
			k = j;
			i++;
			free(sub_line);
		}

	}
	free(line);
}

void	parse_err_or_exec_cmds(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_cmds)
	{
		data->all_parsed[i].pipex = NULL;
		i++;
	}
	if (data->all_parsed && data->all_parsed->err_code != EXIT_SUCCESS)
	{
		data->exit_code = data->all_parsed->err_code;
		ft_strerror(data, NULL, NULL, data->all_parsed->err_msg);
	}
	else
		data->exit_code = exec_cmds(data);
}

void	prompt(t_data *data)
{
	char	*line;

	while (1)
	{
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
			obtain_cmds(data, line); // не моя функция
			parse_err_or_exec_cmds(data);
			ft_free_t_cmd(data);
			free_all_parsed(data->all_parsed, data->nb_cmds); // не моя функция
			data->nb_cmds = 0;
		}
	}
	// rl_clear_history (); // Не компилирует с ним на mac из-за этого закоментирован
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data				*data;
	// struct sigaction	sa;
	// struct sigaction	saq;

	if (argc != 1)
		(printf("No arguments needed\n"), exit(EXIT_FAILURE));

	// код сигналов коллеги который я убрала.

	data = init_builtins(argv, envp);
	prompt(data);
	exit_builtin(data, NULL, false); // si i/y a un problemme dans promt et il arrive jusqu'ici, et on efface notre memoire
	return (EXIT_SUCCESS);
}
