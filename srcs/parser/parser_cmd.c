/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:16:04 by alex              #+#    #+#             */
/*   Updated: 2024/08/08 16:25:50 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

cmd_node	*cmd_simple(t_token **token);
cmd_node	*cmd_argument(t_token **token);
cmd_node	*argument(t_token **token);

cmd_node	*cmd_simple(t_token **token)
{
	cmd_node	*arg;
	cmd_node	*result;
	char		*res;

	if (!check_tokentype(TOKEN, token, &res))
	{
		free(res);
		return (NULL);
	}
	arg = cmd_argument(token);
	result = malloc(sizeof(cmd_node));
	cmd_set_type(result, NODE_CMDPATH);
	cmd_set_data(result, res);
	cmd_attach(result, NULL, arg);
	return (result);
}

cmd_node	*cmd_argument(t_token **token)
{
	t_token		*save;
	cmd_node	*node;

	save = *token;
	*token = save;
	node = argument(token);
	if (node)
		return (node);
	*token = save;
	if (node == NULL)
		return (node);
	return (NULL);
}

cmd_node	*argument(t_token **token)
{
	cmd_node	*arg;
	cmd_node	*result;
	char		*res;

	if (!check_tokentype(TOKEN, token, &res))
		return (NULL);
	arg = cmd_argument(token);
	result = malloc(sizeof(cmd_node));
	cmd_set_type(result, NODE_ARGUMENT);
	cmd_set_data(result, res);
	cmd_attach(result, NULL, arg);
	return (result);
}

cmd_node	*cmd(t_token **token)
{
	t_token		*save;
	cmd_node	*node;

	save = *token;
	*token = save;
	node = redirect(token);
	if (node)
		return (node);
	*token = save;
	node = cmd_simple(token);
	if (node)
		return (node);
	return (NULL);
}
