/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:10 by algultse          #+#    #+#             */
/*   Updated: 2024/07/16 13:18:11 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_data *data, char *key)
{
	if (!data)
		return (EXIT_FAILURE);
	if (!key || key[0] == '\0')
		return (EXIT_SUCCESS);
	if (!ft_isstralnum(key))
	{
		ft_strerror(data, "unset", key, INVALID_ID);
		return (EXIT_FAILURE);
	}
	if (!ft_strcmp(key, "PWD"))
	{
		modif_env(data, key, "");
		hide_env(data, key);
	}
	else
		delete_env(data, key);
	return (EXIT_SUCCESS);
}
