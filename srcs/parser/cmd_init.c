/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:27:14 by alex              #+#    #+#             */
/*   Updated: 2024/08/18 15:55:13 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

cmd_node	*cmd_define(cmd_node *root, node_type type,
							cmd_node *left, cmd_node *right)
{
	if (right && right->type && right->type == NODE_ERROR)
	{
		if (root)
			cmd_delete(root);
		if (left)
			cmd_delete(left);
		return (right);
	}
	cmd_set_type(root, type);
	cmd_attach(root, left, right);
	return (root);
}

void	cmd_attach(cmd_node *root, cmd_node *left, cmd_node *right)
{
	if (root == NULL)
		return ;
	root->left = left;
	root->right = right;
}

void	cmd_set_type(cmd_node *node, node_type type)
{
	if (node == NULL)
		return ;
	node->type = type;
}

void	cmd_set_data(cmd_node *node, char *data)
{
	if (node == NULL)
		return ;
	if (data != NULL)
	{
		node->data = data;
	}
}

void	cmd_set(cmd_node *node, char *data, node_type type, cmd_node *next)
{
	if (node == NULL)
		return ;
	if (data != NULL)
	{
		node->data = data;
		node->type = type;
		node->left = next;
	}
}
