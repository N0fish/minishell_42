/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:53 by algultse          #+#    #+#             */
/*   Updated: 2024/07/16 13:16:39 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_declare_env(t_data *data, t_envp *list, t_envp **save)
{
	if (!list)
		*save = NULL;
	if (safe_write(data, \
				"export", "declare -x ", STDOUT_FILENO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (safe_write(data, "export", list->key, STDOUT_FILENO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (list->value)
	{
		if (safe_write(data, "export", "=\"", STDOUT_FILENO) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (safe_write(data, \
					"export", list->value, STDOUT_FILENO) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (safe_write(data, "export", "\"", STDOUT_FILENO) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (safe_write(data, "export", "\n", STDOUT_FILENO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*save = list;
	return (EXIT_SUCCESS);
}

bool	should_declare(t_envp *save, t_envp *tmp, t_envp *list)
{
	return ((list && list->key && \
			(!save || ft_strcmp(list->key, save->key) > 0) && \
			(!tmp || ft_strcmp(list->key, tmp->key) < 0) && \
			ft_strcmp(list->key, "_") != 0) && list->display);
}

int	declare_env_builtin(t_data *data)
{
	t_envp	*save;
	t_envp	*tmp;
	t_envp	*list;
	size_t	it;

	if (!data->envp)
		return (EXIT_FAILURE);
	save = NULL;
	it = 0;
	while (it < env_len(data->envp, true))
	{
		list = data->envp;
		tmp = NULL;
		while (list)
		{
			if (should_declare(save, tmp, list))
				tmp = list;
			list = list->next;
		}
		if (tmp)
			if (print_declare_env(data, tmp, &save) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		it++;
	}
	return (EXIT_SUCCESS);
}
