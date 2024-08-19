/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:25:12 by alex              #+#    #+#             */
/*   Updated: 2024/08/19 18:33:31 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_quotes(char ch, t_token **token, int *j, int *state)
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

void	lexer_redirections(char *input, t_token **token, int i, int *j)
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

void	lexer_heredoc(char *input, t_token **t, int *i, int *j)
{
	int		ch_t;

	if (!input || !t || !*t)
		return ;
	ch_t = is_heredoc(input, *i);
	if (ch_t == HEREDOC_IN || ch_t == HEREDOC_OUT)
	{
		(*i) += 1;
		if (*j > 0)
		{
			(*t)->next = token_init((*t)->m, (*t)->next, ft_strlen(input) - *i);
			(*t) = (*t)->next;
			*j = 0;
		}
		(*t)->type = ch_t;
		if (input[*i + 1] && char_type(input[*i + 1]) != CHAR_WHITESPACE)
		{
			(*t)->next = token_init((*t)->m, (*t)->next, ft_strlen(input) - *i);
			(*t) = (*t)->next;
			(*i) += 1;
		}
		if (input[*i] && (input[*i] == '>' || input[*i] == '<'))
			(*i) += 1;
	}
}

void	lexer_general(char *input, t_token **token, int i, int *j)
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

void	lexer_other_state(char ch, t_token **token, int *j, int *state)
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
