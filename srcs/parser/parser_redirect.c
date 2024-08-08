/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:06:27 by alex              #+#    #+#             */
/*   Updated: 2024/08/08 16:25:20 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

cmd_node	*redirect_out(t_token **token);
cmd_node	*redirect_in(t_token **token);

cmd_node	*redirect_in(t_token **token)
{
	cmd_node	*cmd_tok;
	cmd_node	*redirect_tok;
	cmd_node	*result;
	char		*filename;

	cmd_tok = cmd_simple(token);
	if (!cmd_tok)
		return (NULL);
	if (!check_tokentype(CHAR_LESSER, token, NULL))
	{
		cmd_delete(cmd_tok);
		return (NULL);
	}
	if (!only_check_tokentype(TOKEN, token, &filename))
	{
		cmd_delete(cmd_tok);
		return (NULL);
	}
	result = malloc(sizeof(cmd_node));
	redirect_tok = redirect(token);
	if (!redirect_tok)
	{
		cmd_set_type(result, NODE_REDIRECT_IN);
		cmd_set_data(result, filename);
		cmd_attach(result, cmd_tok, NULL);
		return (result);
	}
	cmd_set_type(result, NODE_REDIRECT_IN);
	cmd_set_data(result, filename);
	cmd_attach(result, cmd_tok, redirect_tok);
	return (result);
}

cmd_node	*redirect_out(t_token **token)
{
	cmd_node	*cmd_tok;
	cmd_node	*redirect_tok;
	cmd_node	*result;
	char		*filename;

	cmd_tok = cmd_simple(token);
	if (!cmd_tok)
		return (NULL);
	if (!check_tokentype(CHAR_GREATER, token, NULL))
	{
		cmd_delete(cmd_tok);
		return (NULL);
	}
	if (!only_check_tokentype(TOKEN, token, &filename))
	{
		cmd_delete(cmd_tok);
		return (NULL);
	}
	result = malloc(sizeof(cmd_node));
	redirect_tok = redirect(token);
	if (!redirect_tok)
	{
		cmd_set_type(result, NODE_REDIRECT_OUT);
		cmd_set_data(result, filename);
		cmd_attach(result, cmd_tok, NULL);
		return (result);
	}
	cmd_set_type(result, NODE_REDIRECT_OUT);
	cmd_set_data(result, filename);
	cmd_attach(result, cmd_tok, redirect_tok);
	return (result);
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
