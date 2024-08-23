/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:12:06 by alex              #+#    #+#             */
/*   Updated: 2024/08/23 16:19:31 by alex             ###   ########.fr       */
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
		temp_left->right->type = temp_right->type;
		temp_left->right->data = ft_strdup(temp_right->data);
		if (temp_right->right)
			temp_left->right->right = temp_right->right;
		if (temp_right->left)
			temp_left->right->left = temp_right->left;
		temp_right = temp_right->right;
		temp_left = temp_left->right;
	}
	return (*left);
}

bool	is_heredoc_or_redirect(t_cmd_node *node)
{
	return (node->type == NODE_HEREDOC_OUT
		|| node->type == NODE_HEREDOC_IN
		|| node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_REDIRECT_IN);
}

t_cmd_node	*check_parser(t_cmd_node **node)
{
	t_cmd_node	*head;
	t_cmd_node	*temp;

	if (!node || !*node)
		return (NULL);
	head = *node;
	temp = NULL;
	while (*node)
	{
		if (is_heredoc_or_redirect(*node))
		{
			if (temp && (*node)->left && (*node)->left->right
				&& (*node)->left->right->type == NODE_ARGUMENT)
				add_args_to_node(&temp->left, &(*node)->left->right);
			if (!temp)
				temp = *node;
			if (temp && (*node)->right
				&& (*node)->right->type == NODE_ARGUMENT)
				add_args_to_node(&temp->left, &(*node)->right);
		}
		else
			temp = NULL;
		*node = (*node)->right;
	}
	return (head);
}
