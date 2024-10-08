/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:18:11 by algultse          #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect_node(t_cmd_node *node)
{
	return (node->type == NODE_REDIRECT_IN \
		|| node->type == NODE_REDIRECT_OUT \
		|| node->type == NODE_HEREDOC_IN \
		|| node->type == NODE_HEREDOC_OUT);
}

int	handle_redirect_out(t_data *data, t_cmd_node **node, int *out_fd)
{
	int	open_mode[2];

	open_mode[0] = O_CREAT | O_WRONLY | O_TRUNC;
	open_mode[1] = 0644;
	if (*node && (*node)->type == NODE_REDIRECT_OUT)
		*out_fd = find_final_fd(data, node, NODE_REDIRECT_OUT, open_mode);
	return (*out_fd);
}

int	handle_shift_left(t_data *data, t_cmd_node **node, int *in_fd)
{
	if (*node && (*node)->type == NODE_HEREDOC_OUT)
	{
		*in_fd = handle_heredoc(data, (*node)->data);
		*node = (*node)->right;
	}
	return (*in_fd);
}

int	handle_redirect_in(t_data *data, t_cmd_node **node, int *in_fd)
{
	int	open_mode[2];

	open_mode[0] = O_RDONLY;
	open_mode[1] = DEFAULT_CHMOD;
	if (*node && (*node)->type == NODE_REDIRECT_IN)
		*in_fd = find_final_fd(data, node, NODE_REDIRECT_IN, open_mode);
	return (*in_fd);
}

int	handle_shift_right(t_data *data, t_cmd_node **node, int *out_fd)
{
	int	open_mode[2];

	open_mode[0] = O_CREAT | O_WRONLY | O_APPEND;
	open_mode[1] = 0644;
	if (*node && (*node)->type == NODE_HEREDOC_IN)
		*out_fd = find_final_fd(data, node, NODE_HEREDOC_IN, open_mode);
	return (*out_fd);
}
