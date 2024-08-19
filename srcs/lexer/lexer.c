/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 10:43:03 by alex              #+#    #+#             */
/*   Updated: 2024/08/18 15:36:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token)
{
	while (token)
	{
		ft_printf("data: %s\n", token->data);
		ft_printf("type: %d\n", token->type);
		token = token->next;
	}
}

t_token	*lexer(t_data *data, char *line)
{
	t_token		*token;

	token = lexer_build(data, line, STATE_GENERAL);
	return (token);
}
