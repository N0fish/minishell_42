/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:06:27 by alex              #+#    #+#             */
/*   Updated: 2024/08/18 15:58:55 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

cmd_node	*redirect_out(t_token **token);
cmd_node	*redirect_in(t_token **token);

cmd_node	*redirect_in(t_token **token)
{
	t_token		*save;
	cmd_node	*cmd_tok;
	cmd_node	*redirect_tok;
	cmd_node	*result;
	char		*filename;

	save = *token;
	cmd_tok = cmd_simple(token);
	if (!cmd_tok)
	{
		*token = save;
		cmd_tok = set_null(token);
	}
	if (!check_tokentype(CHAR_LESSER, token, NULL))
		return (cmd_delete(cmd_tok));
	if (!only_check_tokentype(TOKEN, token, &filename))
		return (cmd_delete_error(cmd_tok));
	result = malloc(sizeof(cmd_node));
	cmd_set_data(result, filename);
	redirect_tok = heredoc_or_redirecit(token);
	if (!redirect_tok)
		return (cmd_define(result, NODE_REDIRECT_IN, cmd_tok, NULL));
	return (cmd_define(result, NODE_REDIRECT_IN, cmd_tok, redirect_tok));
}

cmd_node	*redirect_out(t_token **token)
{
	t_token		*save;
	cmd_node	*cmd_tok;
	cmd_node	*redirect_tok;
	cmd_node	*result;
	char		*filename;

	save = *token;
	cmd_tok = cmd_simple(token);
	if (!cmd_tok)
	{
		*token = save;
		cmd_tok = set_null(token);
	}
	if (!check_tokentype(CHAR_GREATER, token, NULL))
		return (cmd_delete(cmd_tok));
	if (!only_check_tokentype(TOKEN, token, &filename))
		return (cmd_delete_error(cmd_tok));
	result = malloc(sizeof(cmd_node));
	cmd_set_data(result, filename);
	redirect_tok = heredoc_or_redirecit(token);
	if (!redirect_tok)
		return (cmd_define(result, NODE_REDIRECT_OUT, cmd_tok, NULL));
	return (cmd_define(result, NODE_REDIRECT_OUT, cmd_tok, redirect_tok));
}

cmd_node	*redirect(t_token **token)
{
	t_token		*save;
	cmd_node	*node;

	save = *token;
	*token = save;
	node = redirect_out(token);
	if (node)
		return (node);
	*token = save;
	node = redirect_in(token);
	if (node)
		return (node);
	*token = save;
	*token = (*token)->next;
	return (NULL);
}
