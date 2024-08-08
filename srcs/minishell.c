/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:05:22 by alex              #+#    #+#             */
/*   Updated: 2024/08/08 16:02:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "executor.h"

/*
Как я запускал свою minishell. 
Читаю линюю с помощью getline. Делю на токены с помощью lexer и функции ft_strtok (добавил в libft).

После этого конвертирую токены в структуру t_token с помощью convert_from_tokens.
Использую t_token для создания дерева команд с помощью parser.

После этого использую executor для выполнения команд.
*/

int main()
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    cmd_node *cmd;
    t_token *tokens;

    while (1)
    {
        ft_printf("minishell$ ");
        read = getline(&line, &len, stdin);
        if (read == -1)
        {
            perror("getline");
            return (1);
        }
        if (line && strlen(line) != 0)
        {
            tokens = lexer(line);
            //print_tokens(tokens);
            if (tokens)
            {
                cmd = parser(&tokens);
                printf("\n!!!!show_cmd_tree!!!!\n");
                show_cmd_tree(cmd);
                printf("\n!!!!end_cmd_tree!!!!\n");
                executor(cmd);
                free(tokens);
            }
        }
    }
    free(line);
    return (0);
}