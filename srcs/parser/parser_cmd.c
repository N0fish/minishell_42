/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:16:04 by alex              #+#    #+#             */
/*   Updated: 2024/08/14 13:23:33 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

cmd_node	*cmd_simple(t_token **token);
cmd_node	*cmd_argument(t_token **token);
cmd_node	*argument(t_token **token, int type);

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
	node = argument(token, TOKEN);
	if (node)
		return (node);
	*token = save;
	node = argument(token, TOKEN_QUOTE);
	if (node)
		return (node);
	*token = save;
	node = argument(token, TOKEN_DQUOTE);
	if (node)
		return (node);
	*token = save;
	if (node == NULL)
		return (node);
	return (NULL);
}

static int	get_argument_type(int type)
{
	if (type == TOKEN)
		return (NODE_ARGUMENT);
	else if (type == TOKEN_QUOTE)
		return (NODE_Q_ARGUMENT);
	else if (type == TOKEN_DQUOTE)
		return (NODE_DQ_ARGUMENT);
	return (NODE_ARGUMENT);
}

cmd_node	*argument(t_token **token, int type)
{
	cmd_node	*arg;
	cmd_node	*result;
	char		*res;
	int			arg_type;

	if (!check_tokentype(type, token, &res))
		return (NULL);
	arg = cmd_argument(token);
	result = malloc(sizeof(cmd_node));
	arg_type = get_argument_type(type);
	cmd_set_type(result, arg_type);
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
