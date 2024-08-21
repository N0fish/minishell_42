/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:06:27 by alex              #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_node	*heredoc_out(t_token **token);
t_cmd_node	*heredoc_in(t_token **token);

t_cmd_node	*heredoc_in(t_token **token)
{
	t_token		*save;
	t_cmd_node	*cmd_tok;
	t_cmd_node	*redirect_tok;
	t_cmd_node	*result;
	char		*filename;

	save = *token;
	cmd_tok = cmd_simple(token);
	if (!cmd_tok)
	{
		*token = save;
		cmd_tok = set_null(token);
	}
	if (!check_tokentype(HEREDOC_IN, token, NULL))
		return (cmd_delete(cmd_tok));
	if (!only_check_tokentype(TOKEN, token, &filename))
		return (cmd_delete_error(cmd_tok));
	result = malloc(sizeof(t_cmd_node));
	cmd_set_data(result, filename);
	cmd_attach(result, NULL, NULL);
	redirect_tok = heredoc_or_redirecit(token);
	if (!redirect_tok)
		return (cmd_define(result, NODE_HEREDOC_IN, cmd_tok, NULL));
	return (cmd_define(result, NODE_HEREDOC_IN, cmd_tok, redirect_tok));
}

t_cmd_node	*heredoc_out(t_token **token)
{
	t_token		*save;
	t_cmd_node	*cmd_tok;
	t_cmd_node	*redirect_tok;
	t_cmd_node	*result;
	char		*filename;

	save = *token;
	cmd_tok = cmd_simple(token);
	if (!cmd_tok)
	{
		*token = save;
		cmd_tok = set_null(token);
	}
	if (!check_tokentype(HEREDOC_OUT, token, NULL))
		return (cmd_delete(cmd_tok));
	if (!only_check_tokentype(TOKEN, token, &filename))
		return (cmd_delete_error(cmd_tok));
	result = malloc(sizeof(t_cmd_node));
	cmd_set_data(result, filename);
	cmd_attach(result, NULL, NULL);
	redirect_tok = heredoc_or_redirecit(token);
	if (!redirect_tok)
		return (cmd_define(result, NODE_HEREDOC_OUT, cmd_tok, NULL));
	return (cmd_define(result, NODE_HEREDOC_OUT, cmd_tok, redirect_tok));
}

t_cmd_node	*heredoc(t_token **token)
{
	t_token		*save;
	t_cmd_node	*node;

	save = *token;
	*token = save;
	node = heredoc_in(token);
	if (node)
		return (node);
	*token = save;
	node = heredoc_out(token);
	if (node)
		return (node);
	*token = save;
	*token = (*token)->next;
	return (NULL);
}
