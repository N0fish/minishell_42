/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 13:23:52 by alex              #+#    #+#             */
/*   Updated: 2024/08/17 14:25:25 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
