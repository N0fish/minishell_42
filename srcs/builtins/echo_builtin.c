/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:09:53 by algultse          #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_data *data, t_cmd_node *arg)
{
	int	newline;

	if (!data)
		return (EXIT_FAILURE);
	newline = 1;
	if (arg && arg->data && !ft_strcmp(arg->data, "-n"))
	{
		newline = 0;
		arg = arg->right;
	}
	while (arg)
	{
		if (arg->data && safe_write(data, "echo", \
			arg->data, STDOUT_FILENO) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (arg->right && arg->data)
			if (safe_write(data, "echo", " ", STDOUT_FILENO) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		arg = arg->right;
	}
	if (newline && safe_write(data, \
								"echo", "\n", STDOUT_FILENO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
