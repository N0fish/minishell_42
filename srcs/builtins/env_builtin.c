/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:10:07 by algultse          #+#    #+#             */
/*   Updated: 2024/07/16 13:15:17 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_data *data)
{
	t_envp	*list;
	int		err;

	if (!data)
		return (EXIT_FAILURE);
	list = data->envp;
	if (!list)
		return (EX_NOTFOUND);
	err = EXIT_FAILURE;
	while (list && list->key)
	{
		if (list->display && list->value)
		{
			if (safe_write(NULL, "env", list->key, STDOUT_FILENO) == err)
				return (ECUSTOMFULL);
			if (safe_write(NULL, "env", "=", STDOUT_FILENO) == err)
				return (ECUSTOMFULL);
			if (safe_write(NULL, "env", list->value, STDOUT_FILENO) == err)
				return (ECUSTOMFULL);
			if (safe_write(NULL, "env", "\n", STDOUT_FILENO) == err)
				return (ECUSTOMFULL);
		}
		list = list->next;
	}
	return (EXIT_SUCCESS);
}
