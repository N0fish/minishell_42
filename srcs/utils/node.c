/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:18:11 by algultse          #+#    #+#             */
/*   Updated: 2024/08/12 17:18:18 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect_node(cmd_node *node)
{
	return (node->type == NODE_REDIRECT_IN \
		|| node->type == NODE_REDIRECT_OUT \
		|| node->type == NODE_HEREDOC_IN \
		|| node->type == NODE_HEREDOC_OUT);
}

void	handle_redirect_out(t_data *data, cmd_node **node, int *out_fd)
{
	int	open_mode[2];

	open_mode[0] = O_CREAT | O_WRONLY | O_TRUNC;
	open_mode[1] = 0644;
	if (*node && (*node)->type == NODE_REDIRECT_OUT)
		*out_fd = find_final_fd(data, node, NODE_REDIRECT_OUT, open_mode);
}

void	handle_shift_left(t_data *data, cmd_node **node, int *in_fd)
{
	if (*node && (*node)->type == NODE_HEREDOC_OUT)
	{
		*in_fd = handle_heredoc(data, (*node)->data);
		*node = (*node)->right;
	}
}

void	handle_redirect_in(t_data *data, cmd_node **node, int *in_fd)
{
	int	open_mode[2];

	open_mode[0] = O_RDONLY;
	open_mode[1] = DEFAULT_CHMOD;
	if (*node && (*node)->type == NODE_REDIRECT_IN)
		*in_fd = find_final_fd(data, node, NODE_REDIRECT_IN, open_mode);
}

void	handle_shift_right(t_data *data, cmd_node **node, int *out_fd)
{
	int	open_mode[2];

	open_mode[0] = O_CREAT | O_WRONLY | O_APPEND;
	open_mode[1] = 0644;
	if (*node && (*node)->type == NODE_HEREDOC_IN)
		*out_fd = find_final_fd(data, node, NODE_HEREDOC_IN, open_mode);
}
