/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:25:25 by alex              #+#    #+#             */
/*   Updated: 2024/08/09 21:54:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_argv(t_data *data, cmd_node *arg_node, char **argv)
{
	int	i;

	i = 0;
	while (arg_node != NULL && arg_node->data != NULL && \
		(arg_node->type == NODE_ARGUMENT || arg_node->type == NODE_CMDPATH))
	{
		if (arg_node->data)
			argv[i] = ft_strdup_m(data->m, arg_node->data);
		else
			argv[i] = NULL;
		arg_node = arg_node->right;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	**get_command_args(t_data *data, cmd_node *node)
{
	int			i;
	int			j;
	cmd_node	*arg_node;
	char		**argv;

	arg_node = node;
	i = 0;
	while (arg_node != NULL && arg_node->data != NULL && \
		(arg_node->type == NODE_ARGUMENT || arg_node->type == NODE_CMDPATH))
	{
		arg_node = arg_node->right;
		i++;
	}
	argv = (char **)ft_malloc(data->m, sizeof(char *) * (i + 1));
	if (!argv)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		argv[j] = NULL;
		j++;
	}
	return (fill_argv(data, node, argv));
}
