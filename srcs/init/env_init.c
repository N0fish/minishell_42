/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:34 by algultse          #+#    #+#             */
/*   Updated: 2024/07/22 12:17:03 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	copy_env_utils(t_data *data, t_envp	**start, t_envp	**tmp)
{
	if (!data)
		return (false);
	if (!data->envp)
	{
		*start = *tmp;
		data->envp = *tmp;
	}
	else
	{
		data->envp->next = *tmp;
		(*tmp)->prev = data->envp;
		data->envp = data->envp->next;
	}
	return (true);
}

bool	copy_env(t_data *data, char **envp)
{
	t_envp	*tmp;
	t_envp	*start;

	if (!data)
		return (false);
	data->envp = NULL;
	if (!envp || !*envp)
		return (true);
	start = data->envp;
	while (*envp)
	{
		tmp = new_env_block(data, envp);
		if (!tmp)
			return (false);
		if (!copy_env_utils(data, &start, &tmp))
			return (false);
		envp++;
	}
	data->envp = start;
	return (true);
}
