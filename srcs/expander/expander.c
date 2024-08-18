/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:41:01 by alex              #+#    #+#             */
/*   Updated: 2024/08/18 14:07:36 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

cmd_node	*expander(t_data *data, cmd_node *node)
{
	cmd_node	*head;

	if (!data || !node)
		return (NULL);
	head = node;
	while (node)
	{
		if (node->type == NODE_DQ_ARGUMENT || node->type == NODE_ARGUMENT)
		{
			node->data = check_vars(data, node->data);
			node->type = NODE_ARGUMENT;
		}
		else if (node->type == NODE_Q_ARGUMENT)
			node->type = NODE_ARGUMENT;
		else if (node->type == NODE_PIPE)
		{
			node->left = expander(data, node->left);
			node->right = expander(data, node->right);
		}
		else if (node->type == NODE_REDIRECT_IN
			|| node->type == NODE_REDIRECT_OUT)
			node->left = expander(data, node->left);
		node = node->right;
	}
	return (head);
}
