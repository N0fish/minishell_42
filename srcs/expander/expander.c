/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:41:01 by alex              #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_node_type(int type)
{
	if (type == NODE_CMDPATH)
		return (NODE_CMDPATH);
	else if (type == NODE_Q_CMDPATH)
		return (NODE_CMDPATH);
	else if (type == NODE_DQ_CMDPATH)
		return (NODE_CMDPATH);
	else if (type == NODE_ARGUMENT)
		return (NODE_ARGUMENT);
	else if (type == NODE_Q_ARGUMENT)
		return (NODE_ARGUMENT);
	else if (type == NODE_DQ_ARGUMENT)
		return (NODE_ARGUMENT);
	return (NODE_ARGUMENT);
}

char	*check_vars(t_data *data, char *str)
{
	if (!str)
		return (NULL);
	str = is_there_env(data, str);
	return (str);
}

t_cmd_node	*replace_node(t_data *data, t_cmd_node **node)
{
	t_cmd_node	*temp;

	while (node && *node && (*node)->right
		&& (*node)->right->type == NODE_ARGUMENT)
	{
		temp = (*node)->right;
		(*node)->right = temp->right;
		(*node)->data = check_vars(data, ft_strdup(temp->data));
		if (temp->data)
			free(temp->data);
		free(temp);
		(*node)->type = NODE_CMDPATH;
		if ((*node)->data)
			break ;
	}
	return (*node);
}

t_cmd_node	*check_node(t_data *data, t_cmd_node **node)
{
	if (!node)
		return (NULL);
	if ((*node)->type == NODE_DQ_ARGUMENT || (*node)->type == NODE_ARGUMENT
		|| (*node)->type == NODE_DQ_CMDPATH || (*node)->type == NODE_CMDPATH)
	{
		(*node)->data = check_vars(data, (*node)->data);
		if (*node && (*node)->type == NODE_CMDPATH && !(*node)->data)
			*node = replace_node(data, node);
		else
			(*node)->type = get_node_type((*node)->type);
	}
	else if ((*node)->type == NODE_Q_ARGUMENT
		|| (*node)->type == NODE_Q_CMDPATH)
		(*node)->type = get_node_type((*node)->type);
	else if ((*node)->type == NODE_REDIRECT_IN
		|| (*node)->type == NODE_REDIRECT_OUT)
		(*node)->data = check_vars(data, (*node)->data);
	return (*node);
}

t_cmd_node	*expander(t_data *data, t_cmd_node *node)
{
	t_cmd_node	*head;

	if (!data || !node)
		return (NULL);
	head = node;
	while (node)
	{
		node = check_node(data, &node);
		if (node->type == NODE_PIPE)
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
