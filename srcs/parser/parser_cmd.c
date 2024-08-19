/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:16:04 by alex              #+#    #+#             */
/*   Updated: 2024/08/19 17:11:55 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

static int	get_cmd_type(int type)
{
	if (type == TOKEN)
		return (NODE_CMDPATH);
	else if (type == TOKEN_QUOTE)
		return (NODE_Q_CMDPATH);
	else if (type == TOKEN_DQUOTE)
		return (NODE_DQ_CMDPATH);
	return (NODE_CMDPATH);
}

cmd_node	*cmd_simple(t_token **token)
{
	cmd_node	*arg;
	cmd_node	*result;
	char		*res;
	int			type;

	if (!(*token))
		return (NULL);
	type = (*token)->type;
	if ((type != TOKEN) && (type != TOKEN_QUOTE)
		&& (type != TOKEN_DQUOTE))
		return (NULL);
	if (!check_tokentype(type, token, &res))
		return (NULL);
	arg = cmd_argument(token);
	result = malloc(sizeof(cmd_node));
	cmd_set_type(result, get_cmd_type(type));
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
	node = heredoc_or_redirecit(token);
	if (node)
		return (node);
	*token = save;
	node = cmd_simple(token);
	if (node)
		return (node);
	return (NULL);
}
