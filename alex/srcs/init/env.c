/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:20:32 by algultse          #+#    #+#             */
/*   Updated: 2024/07/22 12:19:06 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*seek_env(t_envp *envp, char *key)
{
	if (!envp)
		return (NULL);
	while (envp)
	{
		if (!ft_strcmp(key, envp->key))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

char	*seek_env_value(t_envp *envp, char *name)
{
	t_envp	*res;

	if (!envp)
		return (NULL);
	res = seek_env(envp, name);
	if (res)
		return (res->value);
	return (NULL);
}

int	modif_env(t_data *data, char *key, char *value)
{
	t_envp	*list;

	if (!data)
		return (EXIT_FAILURE);
	list = data->envp;
	while (list)
	{
		if (list->key && ft_strlen(list->key) > 0 && !ft_strcmp(key, list->key))
		{
			ft_free(data->m, list->value);
			list->value = NULL;
			if (value)
				list->value = ft_strdup_m(data->m, value);
			return (EXIT_SUCCESS);
		}
		list = list->next;
	}
	return (EXIT_FAILURE);
}

t_envp	*new_block(t_data *data, char *key, char *value)
{
	t_envp	*block;

	if (!data)
		return (NULL);
	block = new_env_block(data, NULL);
	if (key)
	{
		block->key = key;
		block->value = value;
		block->display = true;
	}
	return (block);
}

bool	add_env(t_data *data, char *key, char *value)
{
	t_envp	*list;
	t_envp	*tmp;
	char	*dup_value;

	if (!data)
		return (false);
	dup_value = NULL;
	if (value)
		dup_value = ft_strdup_m(data->m, value);
	if (!data->envp)
	{
		data->envp = new_block(data, \
			ft_strdup_m(data->m, key), dup_value);
		return (data->envp != NULL);
	}
	list = data->envp;
	while (list && list->next != NULL)
		list = list->next;
	tmp = new_block(data, \
		ft_strdup_m(data->m, key), dup_value);
	if (!tmp)
		return (false);
	list->next = tmp;
	tmp->prev = list;
	return (true);
}
