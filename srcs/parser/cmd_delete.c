/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:06:35 by alex              #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_node	*cmd_delete(t_cmd_node *node)
{
	if (!node)
		return (NULL);
	if (node->data)
		free(node->data);
	if (node->left)
		cmd_delete(node->left);
	if (node->right)
		cmd_delete(node->right);
	free(node);
	return (NULL);
}

t_cmd_node	*cmd_delete_error(t_cmd_node *node)
{
	t_cmd_node	*ret;

	cmd_delete(node);
	ret = malloc(sizeof(t_cmd_node));
	ret->data = NULL;
	cmd_set_type(ret, NODE_ERROR);
	cmd_attach(ret, NULL, NULL);
	return (ret);
}

t_cmd_node	*set_null(t_token **token)
{
	t_cmd_node	*result;

	(void)token;
	result = malloc(sizeof(t_cmd_node));
	result->data = NULL;
	cmd_set_type(result, NODE_CMDPATH);
	cmd_attach(result, NULL, NULL);
	return (result);
}
