/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:29:08 by alex              #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_node	*job_pipe(t_token **token);
t_cmd_node	*job(t_token **token);

t_cmd_node	*job(t_token **token)
{
	t_token		*save;
	t_cmd_node	*node;

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

t_cmd_node	*job_pipe(t_token **token)
{
	t_cmd_node	*cmd_tok;
	t_cmd_node	*job_tok;
	t_cmd_node	*result;

	cmd_tok = cmd(token);
	if (!cmd_tok)
		return (NULL);
	if (cmd_tok->type == NODE_ERROR)
		return (cmd_tok);
	if (!check_tokentype(CHAR_PIPE, token, NULL))
		return (cmd_delete(cmd_tok));
	if (!only_check_tokentype(TOKEN, token, NULL))
		return (cmd_delete_error(cmd_tok));
	job_tok = job(token);
	if (!job_tok)
		return (cmd_delete_error(cmd_tok));
	result = malloc(sizeof(t_cmd_node));
	result->data = NULL;
	cmd_attach(result, NULL, NULL);
	return (cmd_define(result, NODE_PIPE, cmd_tok, job_tok));
}

t_cmd_node	*parser(t_data *data, t_token **token)
{
	t_cmd_node	*cmd_tree;

	cmd_tree = job(token);
	if ((cmd_tree && cmd_tree->type == NODE_ERROR) || !cmd_tree)
	{
		data->exit_code = 2;
		cmd_delete(cmd_tree);
		ft_strerror(data, NULL, NULL, "Syntax error");
		return (NULL);
	}
	return (cmd_tree);
}
