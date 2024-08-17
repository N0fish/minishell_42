/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:06:35 by alex              #+#    #+#             */
/*   Updated: 2024/08/17 11:28:14 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_tokentype(int tok_type, t_token **token, char **bufferptr)
{
	if (!(*token))
		return (false);
	if ((*token)->type == tok_type)
	{
		if (bufferptr != NULL)
		{
			*bufferptr = malloc(strlen((*token)->data) + 1);
			strcpy(*bufferptr, (*token)->data);
		}
		*token = (*token)->next;
		return (true);
	}
	*token = (*token)->next;
	return (false);
}

bool	only_check_tokentype(int tok_type, t_token **token, char **bufferptr)
{
	if (!(*token))
		return (false);
	if ((*token)->type == tok_type)
	{
		if (bufferptr != NULL)
		{
			*bufferptr = malloc(strlen((*token)->data) + 1);
			strcpy(*bufferptr, (*token)->data);
		}
		return (true);
	}
	return (false);
}

void	show_cmd_tree(cmd_node *node)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_CMDPATH)
	{
		printf("cmd: %s\n", node->data);
	}
	else if (node->type == NODE_ARGUMENT
		|| node->type == NODE_Q_ARGUMENT
		|| node->type == NODE_DQ_ARGUMENT)
	{
		printf("arg: %s\n", node->data);
		printf("type: %d\n", node->type);
	}
	else if (node->type == NODE_PIPE)
	{
		printf("pipe: %s | %s\n", node->left->data, node->right->data);
	}
	else if (node->type == NODE_REDIRECT_OUT)
	{
		printf("redirect out: %s > %s\n", node->left->data, node->data);
	}
	else if (node->type == NODE_REDIRECT_IN)
	{
		printf("redirect in: %s < %s\n", node->left->data, node->data);
	}
	show_cmd_tree(node->right);
}

cmd_node	*cmd_delete(cmd_node *node)
{
	if (!node)
		return (NULL);
	if (node->type >= 0)
		free(node->data);
	cmd_delete(node->left);
	cmd_delete(node->right);
	free(node);
	return (NULL);
}
