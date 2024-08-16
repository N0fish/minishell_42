/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:56:53 by alex              #+#    #+#             */
/*   Updated: 2024/08/16 17:29:34 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	char_type(char ch)
{
	if (ch == '|')
		return (CHAR_PIPE);
	else if (ch == '>')
		return (CHAR_GREATER);
	else if (ch == '<')
		return (CHAR_LESSER);
	else if (ch == '\'')
		return (CHAR_QOUTE);
	else if (ch == '\"')
		return (CHAR_DQOUTE);
	else if (ch == ' ')
		return (CHAR_WHITESPACE);
	else if (ch == 0)
		return (CHAR_NULL);
	else
		return (CHAR_GENERAL);
}

void	strip_quotes(char *src, char *dest)
{
	int		n;
	int		i;
	int		j;
	char	lastquote;

	lastquote = 0;
	j = 0;
	i = -1;
	n = ft_strlen(src);
	if (n <= 1)
	{
		ft_strcpy(dest, src);
		return ;
	}
	while (++i < n)
	{
		if ((src[i] == '\'' || src[i] == '\"') && lastquote == 0)
			lastquote = src[i];
		else if (src[i] == lastquote)
			lastquote = 0;
		else
			dest[j++] = src[i];
	}
	dest[j] = 0;
}

t_token	*check_lexer(t_data *data, t_token *token, int state)
{
	t_token	*head;

	head = token;
	if (state != STATE_GENERAL)
	{
		ft_strerror(data, NULL, NULL, "Syntax error");
		lexer_destroy(&head);
		return (NULL);
	}
	while (token)
	{
		if (token->type == TOKEN || token->type == TOKEN_DQUOTE
			|| token->type == TOKEN_QUOTE)
			strip_quotes(token->data, token->data);
		token = token->next;
	}
	token = head;
	return (token);
}

void	lexer_destroy(t_token **token)
{
	if (token && *token)
	{
		free((*token)->data);
		lexer_destroy(&(*token)->next);
		free(*token);
	}
}
