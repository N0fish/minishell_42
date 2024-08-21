/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:25:25 by alex              #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**fill_argv(t_data *data, t_cmd_node *arg_node, char **argv)
{
	int	i;

	i = 0;
	while (arg_node != NULL && \
		(arg_node->type == NODE_ARGUMENT || arg_node->type == NODE_CMDPATH))
	{
		if (arg_node->data)
			argv[i++] = ft_strdup_m(data->m, arg_node->data);
		arg_node = arg_node->right;
	}
	argv[i] = NULL;
	return (argv);
}

char	**get_command_args(t_data *data, t_cmd_node *node)
{
	int			i;
	int			j;
	t_cmd_node	*arg_node;
	char		**argv;

	arg_node = node;
	i = 0;
	while (arg_node != NULL && \
		(arg_node->type == NODE_ARGUMENT || arg_node->type == NODE_CMDPATH))
	{
		if (arg_node->data != NULL)
			i++;
		arg_node = arg_node->right;
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
