/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:06:35 by alex              #+#    #+#             */
/*   Updated: 2024/08/19 18:43:57 by aliutykh         ###   ########.fr       */
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
			*bufferptr = malloc(ft_strlen((*token)->data) + 1);
			ft_strcpy(*bufferptr, (*token)->data);
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
	if ((*token)->type == tok_type
		|| ((tok_type == TOKEN)
			&& ((*token)->type == TOKEN_QUOTE
				|| (*token)->type == TOKEN_DQUOTE
				|| (*token)->type == TOKEN)))
	{
		if (bufferptr != NULL)
		{
			*bufferptr = malloc(ft_strlen((*token)->data) + 1);
			ft_strcpy(*bufferptr, (*token)->data);
		}
		return (true);
	}
	return (false);
}

cmd_node	*heredoc_or_redirecit(t_token **token)
{
	t_token		*save;
	cmd_node	*node;

	save = *token;
	*token = save;
	node = heredoc(token);
	if (node)
		return (node);
	*token = save;
	node = redirect(token);
	if (node)
		return (node);
	*token = save;
	*token = (*token)->next;
	return (NULL);
}

/*
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
	else if (node->type == NODE_HEREDOC_OUT)
	{
		printf("heredoc out: %s << %s\n", node->left->data, node->data);
	}
	else if (node->type == NODE_HEREDOC_IN)
	{
		printf("heredoc in: %s >> %s\n", node->left->data, node->data);
	}
	show_cmd_tree(node->right);
}
*/