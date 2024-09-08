/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:19:39 by algultse          #+#    #+#             */
/*   Updated: 2024/09/08 11:59:48 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*empty_block(t_data *data)
{
	t_envp	*tmp;

	tmp = (t_envp *)ft_malloc(data->m, sizeof(t_envp));
	if (!tmp)
		return (NULL);
	tmp->prev = NULL;
	tmp->next = NULL;
	tmp->value = NULL;
	tmp->key = NULL;
	return (tmp);
}

void	modif_or_add_env(t_data *data, char *key, char *value)
{
	if (seek_env(data->envp, key))
		modif_env(data, key, value);
	else
		add_env(data, key, value);
}

void	delete_env(t_data *data, char *key)
{
	t_envp	*list;

	list = data->envp;
	while (list)
	{
		if (!ft_strcmp(key, list->key))
		{
			list->display = false;
			if (list->value)
				ft_free(data->m, list->value);
			if (list->key)
				ft_free(data->m, list->key);
			if (list->prev)
				list->prev->next = list->next;
			if (list->next)
				list->next->prev = list->prev;
			ft_free(data->m, list);
			return ;
		}
		list = list->next;
	}
}

void	hide_env(t_data *data, char *key)
{
	t_envp	*list;

	list = data->envp;
	while (list)
	{
		if (!ft_strcmp(key, list->key))
		{
			list->display = false;
			return ;
		}
		list = list->next;
	}
}

size_t	env_len(t_envp *envp, bool has_display)
{
	size_t	len;

	len = 0;
	while (envp)
	{
		if (has_display && envp->display == false)
		{
			envp = envp->next;
			continue ;
		}
		envp = envp->next;
		len++;
	}
	return (len);
}
