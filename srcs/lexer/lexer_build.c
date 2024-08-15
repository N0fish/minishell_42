/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:23:52 by alex              #+#    #+#             */
/*   Updated: 2024/08/14 13:01:23 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	lexer_quotes(char ch, t_token **token, int *j, int *state)
{
	if (!token || !*token)
		return ;
	if (char_type(ch) == CHAR_QOUTE)
	{
		*state = STATE_IN_QUOTE;
		(*token)->data[(*j)++] = CHAR_QOUTE;
		(*token)->type = TOKEN_QUOTE;
	}
	else if (char_type(ch) == CHAR_DQOUTE)
	{
		*state = STATE_IN_DQUOTE;
		(*token)->data[(*j)++] = CHAR_DQOUTE;
		(*token)->type = TOKEN_DQUOTE;
	}
}

static void	lexer_redirections(char *input, t_token **token, int i, int *j)
{
	int		ch_t;

	if (!input || !token || !*token)
		return ;
	ch_t = char_type(input[i]);
	if (ch_t == CHAR_PIPE || ch_t == CHAR_GREATER || ch_t == CHAR_LESSER)
	{
		if (*j > 0)
		{
			(*token)->data[*j] = 0;
			(*token)->next = malloc(sizeof(t_token));
			(*token) = (*token)->next;
			token_data_init(*token, ft_strlen(input) - i);
			*j = 0;
		}
		(*token)->data[0] = input[i];
		(*token)->data[1] = 0;
		(*token)->type = ch_t;
		if (input[i + 1] && char_type(input[i + 1]) != CHAR_WHITESPACE)
		{
			(*token)->next = malloc(sizeof(t_token));
			(*token) = (*token)->next;
			token_data_init(*token, ft_strlen(input) - i);
		}
	}
}

static void	lexer_general(char *input, t_token **token, int i, int *j)
{
	if (!input || !token || !*token)
		return ;
	if (char_type(input[i]) == CHAR_GENERAL)
	{
		(*token)->data[(*j)++] = input[i];
		(*token)->type = TOKEN;
	}
	else if (char_type(input[i]) == CHAR_WHITESPACE
		&& input[i + 1] && char_type(input[i + 1]) != CHAR_WHITESPACE)
	{
		if (j > 0)
		{
			(*token)->data[*j] = 0;
			(*token)->next = malloc(sizeof(t_token));
			(*token) = (*token)->next;
			token_data_init(*token, ft_strlen(input) - i);
			*j = 0;
		}
	}
}

static void	lexer_other_state(char ch, t_token **token, int *j, int *state)
{
	if (!token || !*token)
		return ;
	if (*state == STATE_IN_QUOTE)
	{
		(*token)->data[(*j)++] = ch;
		if (char_type(ch) == CHAR_QOUTE)
			*state = STATE_GENERAL;
	}
	else if (*state == STATE_IN_DQUOTE)
	{
		(*token)->data[(*j)++] = ch;
		if (char_type(ch) == CHAR_DQOUTE)
			*state = STATE_GENERAL;
	}
	if (char_type(ch) == CHAR_NULL)
	{
		if (*j > 0)
		{
			(*token)->data[*j] = 0;
			*j = 0;
		}
	}
}

t_token	*lexer_build(char *input, int state)
{
	t_token		*token;
	t_token		*head;
	int			i;
	int			j;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	head = token;
	token_data_init(token, ft_strlen(input));
	i = -1;
	j = 0;
	while (input[++i])
	{
		if (state == STATE_GENERAL)
		{
			lexer_quotes(input[i], &token, &j, &state);
			lexer_redirections(input, &token, i, &j);
			lexer_general(input, &token, i, &j);
		}
		else
			lexer_other_state(input[i], &token, &j, &state);
	}
	remove_quotes_from(head);
	return (head);
}
