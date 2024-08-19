/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:56:53 by alex              #+#    #+#             */
/*   Updated: 2024/08/19 17:11:31 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_data_init(t_token *token, int size)
{
	if (!token)
		return ;
	if (token->m)
		token->data = (char *)ft_malloc(token->m, sizeof(char) * (size + 1));
	else
		token->data = malloc(sizeof(char) * (size + 1));
	token->data[0] = 0;
	token->type = CHAR_NULL;
	token->next = NULL;
}

t_token	*token_init(t_malloc *m, t_token *token, int size)
{
	token = (t_token *)ft_malloc(m, sizeof(t_token));
	token->m = m;
	token_data_init(token, size);
	return (token);
}
