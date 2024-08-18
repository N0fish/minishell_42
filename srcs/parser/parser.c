/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:29:08 by alex              #+#    #+#             */
/*   Updated: 2024/08/18 15:55:21 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include "minishell.h"

/*
I try to parse the structure to make it working with pipes:

JOB :: { CMD | JOB } { CMD }
CMD :: { CMD_SIMPLE > CMD } { CMD_SIMPLE < CMD } { CMD_SIMPLE }
*/

cmd_node	*job_pipe(t_token **token);
cmd_node	*job(t_token **token);

cmd_node	*job(t_token **token)
{
	t_token		*save;
	cmd_node	*node;

	save = *token;
	*token = save;
	node = job_pipe(token);
	if (node)
		return (node);
	*token = save;
	node = cmd(token);
	if (node)
		return (node);
	return (NULL);
}

cmd_node	*job_pipe(t_token **token)
{
	cmd_node	*cmd_tok;
	cmd_node	*job_tok;
	cmd_node	*result;

	cmd_tok = cmd(token);
	if (!cmd_tok)
		return (NULL);
	if (!check_tokentype(CHAR_PIPE, token, NULL))
		return (cmd_delete(cmd_tok));
	if (!only_check_tokentype(TOKEN, token, NULL))
		return (cmd_delete_error(cmd_tok));
	job_tok = job(token);
	if (!job_tok)
		return (cmd_delete_error(cmd_tok));
	result = malloc(sizeof(cmd_node));
	return (cmd_define(result, NODE_PIPE, cmd_tok, job_tok));
}

cmd_node	*parser(t_data *data, t_token **token)
{
	cmd_node	*cmd_tree;

	cmd_tree = job(token);
	if (cmd_tree && cmd_tree->type == NODE_ERROR)
	{
		cmd_delete(cmd_tree);
		ft_strerror(data, NULL, NULL, "Syntax error");
		return (NULL);
	}
	return (cmd_tree);
}
