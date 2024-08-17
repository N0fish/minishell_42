/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:23:52 by alex              #+#    #+#             */
/*   Updated: 2024/08/17 12:56:59 by alex             ###   ########.fr       */
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
			(*token)->data[*j] = '\0';
			(*token)->next = token_init((*token)->m,
					(*token)->next, ft_strlen(input) - i);
			(*token) = (*token)->next;
			*j = 0;
		}
		(*token)->data[0] = input[i];
		(*token)->data[1] = '\0';
		(*token)->type = ch_t;
		if (input[i + 1] && char_type(input[i + 1]) != CHAR_WHITESPACE)
		{
			(*token)->next = token_init((*token)->m,
					(*token)->next, ft_strlen(input) - i);
			(*token) = (*token)->next;
		}
	}
}

static void	lexer_heredoc(char *input, t_token **token, int *i, int *j)
{
	int		ch_t;

	if (!input || !token || !*token)
		return ;
	ch_t = is_heredoc(input, *i);
	if (ch_t == HEREDOC_IN || ch_t == HEREDOC_OUT)
	{
		(*i) += 1;
		if (*j > 0)
		{
			(*token)->data[*j] = '\0';
			(*token)->next = token_init((*token)->m,
					(*token)->next, ft_strlen(input) - *i);
			(*token) = (*token)->next;
			*j = 0;
		}
		(*token)->data[0] = input[*i];
		(*token)->data[1] = '\0';
		(*token)->type = ch_t;
		if (input[*i + 1] && char_type(input[*i + 1]) != CHAR_WHITESPACE)
		{
			(*token)->next = token_init((*token)->m,
					(*token)->next, ft_strlen(input) - *i);
			(*token) = (*token)->next;
			(*i) += 1;
		}
		if (input[*i] == '>' || input[*i] == '<')
			(*i) += 1;
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
		if (j != NULL)
		{
			(*token)->data[*j] = '\0';
			(*token)->next = token_init((*token)->m,
					(*token)->next, ft_strlen(input) - i);
			(*token) = (*token)->next;
			*j = 0;
		}
	}
	if (char_type(input[i]) == CHAR_NULL)
	{
		if (*j > 0)
			(*token)->data[*j] = '\0';
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
}

t_token	*lexer_build(t_data *data, char *input, int state)
{
	t_token		*token;
	t_token		*head;
	int			i;
	int			j;

	token = NULL;
	token = token_init(data->m, token, ft_strlen(input));
	head = token;
	i = -1;
	j = 0;
	while (input[++i])
	{
		if (state == STATE_GENERAL)
		{
			lexer_quotes(input[i], &token, &j, &state);
			lexer_heredoc(input, &token, &i, &j);
			lexer_redirections(input, &token, i, &j);
			lexer_general(input, &token, i, &j);
		}
		else
			lexer_other_state(input[i], &token, &j, &state);
	}
	lexer_general(input, &token, i, &j);
	return (check_lexer(data, head, state));
}
