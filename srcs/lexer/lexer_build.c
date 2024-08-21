/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:23:52 by alex              #+#    #+#             */
/*   Updated: 2024/08/21 17:52:31 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_null(char *input, t_token **token, int i, int *j)
{
	if (!token || !*token)
		return ;
	if (char_type(input[i]) == CHAR_GENERAL
		&& (char_type(input[i + 1]) != CHAR_GENERAL))
	{
		if (*j > 0)
			(*token)->data[(*j)] = '\0';
	}
}

void	lexer_others(char *input, t_token **token, int *i, int *j)
{
	if (!token || !*token)
		return ;
	lexer_heredoc(input, token, i, j);
	lexer_redirections(input, token, *i, j);
	lexer_general(input, token, *i, j);
	lexer_null(input, token, *i, j);
}

t_token	*skip_spaces(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' '
			|| (input[*i] >= '\t' && input[*i] <= '\r')))
		(*i)++;
	(*i)--;
	return (NULL);
}

t_token	*lexer_build(t_data *data, char *input, int state)
{
	t_token		*token;
	t_token		*head;
	int			i;
	int			j;

	i = 0;
	j = 0;
	token = skip_spaces(input, &i);
	token = token_init(data->m, token, ft_strlen(input));
	head = token;
	while (input[++i])
	{
		if (state == STATE_GENERAL)
		{
			lexer_quotes(input[i], &token, &j, &state);
			lexer_others(input, &token, &i, &j);
			if (input[i] == '\0')
				break ;
		}
		else
			lexer_other_state(input[i], &token, &j, &state);
	}
	if (input[i - 1] != '\0')
		lexer_general(input, &token, i, &j);
	return (check_lexer(data, head, state));
}
