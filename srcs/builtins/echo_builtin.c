/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:09:53 by algultse          #+#    #+#             */
/*   Updated: 2024/07/29 13:05:26 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_data *data, char **arg)
{
	int		newline;
	int		i;

	if (!data)
		return (EXIT_FAILURE);
	newline = 1;
	i = 1;
	if (arg[1] && !ft_strcmp(arg[1], "-n"))
	{
		newline = 0;
		i = 2;
	}
	while (arg[i])
	{
		if (safe_write(data, "echo", arg[i], STDOUT_FILENO) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (arg[i + 1])
			if (safe_write(data, "echo", " ", STDOUT_FILENO) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		i++;
	}
	if (newline && safe_write(data, \
								"echo", "\n", STDOUT_FILENO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
