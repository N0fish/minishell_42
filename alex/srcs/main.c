/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:05:22 by alex              #+#    #+#             */
/*   Updated: 2024/08/04 19:25:20 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Как я запускал свою minishell. 
Читаю линюю с помощью getline. Делю на токены с помощью lexer и функции ft_strtok (добавил в libft).

После этого конвертирую токены в структуру t_token с помощью convert_from_tokens.
Использую t_token для создания дерева команд с помощью parser.

После этого использую executor для выполнения команд.
*/

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char **tokens;
    cmd_node *cmd;
    t_token *token;

    while (1)
    {
        ft_printf("minishell$ ");
        read = getline(&line, &len, stdin);
        if (read == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }
        tokens = lexer(line);
        token = convert_from_tokens(tokens);
        //print_tokens(token);
        cmd = parser(&token);
        printf("\n!!!!show_cmd_tree!!!!\n");
        show_cmd_tree(cmd);
        printf("\n!!!!end_cmd_tree!!!!\n");
        executor(cmd);
        free(tokens);
        free(token);
    }
    free(line);
    return (0);
}