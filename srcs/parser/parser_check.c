/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:12:06 by aliutykh          #+#    #+#             */
/*   Updated: 2024/08/22 18:00:51 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_node	*add_args_to_node(t_cmd_node **left, t_cmd_node **right)
{
	t_cmd_node	*temp_left;
	t_cmd_node	*temp_right;

	temp_left = *left;
	temp_right = *right;
	while (temp_left && temp_left->right)
		temp_left = temp_left->right;
	if (!temp_left->data)
	{
		temp_left->data = ft_strdup(temp_right->data);
		temp_right = temp_right->right;
	}
	while (temp_right)
	{
		temp_left->right = malloc(sizeof(t_cmd_node));
		if (!temp_left->right)
			return (NULL);
		temp_left->right->type = temp_right->type;
		temp_left->right->data = ft_strdup(temp_right->data);
		// if (temp_right->right)
		// 	temp_left->right->right = temp_right->right;
		// if (temp_right->left)
		// 	temp_left->right->left = temp_right->left;
		temp_left->right->left = NULL;
		temp_left->right->right = NULL;
		temp_right = temp_right->right;
		temp_left = temp_left->right;
	}
	return (*left);
}

bool	is_heredoc_or_redirect(t_cmd_node *node)
{
	if (!node)
		return (false);
	return (node->type == NODE_HEREDOC_OUT
		|| node->type == NODE_HEREDOC_IN
		|| node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_REDIRECT_IN);
}

bool	is_argument(t_cmd_node	*node)
{
	if (!node)
		return (false);
	return (node->type == NODE_ARGUMENT
		|| node->type == NODE_Q_ARGUMENT
		|| node->type == NODE_DQ_ARGUMENT);
}

t_cmd_node	*check_parser(t_cmd_node **node)
{
	t_cmd_node	*head;

	if (!node || !*node)
		return (NULL);
	head = *node;
	while (*node)
	{
		if ((*node)->type == NODE_HEREDOC_OUT
			|| (*node)->type == NODE_HEREDOC_IN
			|| (*node)->type == NODE_REDIRECT_OUT
			|| (*node)->type == NODE_REDIRECT_IN)
		{
			if ((*node)->right && (*node)->left
				&& (*node)->right->type == NODE_ARGUMENT)
				add_args_to_node(&(*node)->left, &(*node)->right);
		}
		*node = (*node)->right;
	}
	return (head);
}
