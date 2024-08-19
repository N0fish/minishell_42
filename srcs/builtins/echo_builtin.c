/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:09:53 by algultse          #+#    #+#             */
/*   Updated: 2024/08/12 12:07:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_data *data, cmd_node *arg)
{
	int	newline;

	if (!data)
		return (EXIT_FAILURE);
	newline = 1;
	if (arg && !ft_strcmp(arg->data, "-n"))
	{
		newline = 0;
		arg = arg->right;
	}
	while (arg)
	{
		if (safe_write(data, "echo", arg->data, STDOUT_FILENO) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (arg->right)
			if (safe_write(data, "echo", " ", STDOUT_FILENO) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		arg = arg->right;
	}
	if (newline && safe_write(data, \
								"echo", "\n", STDOUT_FILENO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
