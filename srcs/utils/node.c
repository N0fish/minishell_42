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
		|| node->type == NODE_REDIRECT_OUT);
}
