/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:27:14 by aliutykh          #+#    #+#             */
/*   Updated: 2024/08/21 15:30:24 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_node	*cmd_define(t_cmd_node *root, t_node_type type,
							t_cmd_node *left, t_cmd_node *right)
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

void	cmd_attach(t_cmd_node *root, t_cmd_node *left, t_cmd_node *right)
{
	if (!root)
		return ;
	root->left = left;
	root->right = right;
}

void	cmd_set_type(t_cmd_node *node, t_node_type type)
{
	if (!node)
		return ;
	node->type = type;
}

void	cmd_set_data(t_cmd_node *node, char *data)
{
	if (!node)
		return ;
	node->data = data;
}

void	cmd_set(t_cmd_node *node, char *data, t_node_type type, \
				t_cmd_node *next)
{
	if (!node)
		return ;
	node->data = data;
	node->type = type;
	node->left = next;
}
