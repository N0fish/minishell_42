/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:43:03 by alex              #+#    #+#             */
/*   Updated: 2024/08/08 16:04:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	assign_token_type(char *token)
{
	if (token[0] == '|')
		return (CHAR_PIPE);
	else if (token[0] == '>')
		return (CHAR_GREATER);
	else if (token[0] == '<')
		return (CHAR_LESSER);
	else
		return (TOKEN);
}

static t_token	*convert_from_tokens(char **tokens)
{
	t_token		*head;
	t_token		*prev;
	t_token		*token;
	int			i;

	head = NULL;
	prev = NULL;
	i = -1;
	while (tokens[++i])
	{
		token = malloc(sizeof(t_token));
		token->data = tokens[i];
		token->type = assign_token_type(tokens[i]);
		token->next = NULL;
		if (prev == NULL)
			head = token;
		else
			prev->next = token;
		prev = token;
	}
	free(tokens);
	return (head);
}

void	print_tokens(t_token *token)
{
	while (token)
	{
		ft_printf("data: %s\n", token->data);
		ft_printf("type: %d\n", token->type);
		token = token->next;
	}
}

t_token	*lexer(char *line)
{
	char	**tokens;

	tokens = ft_strtok(line, TOKEN_DELIM);
	return (convert_from_tokens(tokens));
}
