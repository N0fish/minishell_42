/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:06:35 by alex              #+#    #+#             */
/*   Updated: 2024/08/19 18:18:58 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

cmd_node	*cmd_delete(cmd_node *node)
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

cmd_node	*cmd_delete_error(cmd_node *node)
{
	cmd_node	*ret;

	if (!node)
		return (NULL);
	if (node->data)
		free(node->data);
	if (node->left)
		cmd_delete(node->left);
	if (node->right)
		cmd_delete(node->right);
	free(node);
	ret = malloc(sizeof(cmd_node));
	ret->data = NULL;
	cmd_set_type(ret, NODE_ERROR);
	cmd_attach(ret, NULL, NULL);
	return (ret);
}

cmd_node	*set_null(t_token **token)
{
	cmd_node	*result;

	(void)token;
	result = malloc(sizeof(cmd_node));
	result->data = NULL;
	cmd_set_type(result, NODE_CMDPATH);
	cmd_attach(result, NULL, NULL);
	return (result);
}
