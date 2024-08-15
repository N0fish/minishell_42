/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:10 by algultse          #+#    #+#             */
/*   Updated: 2024/08/08 16:45:47 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_data *data, cmd_node *arg)
{
	if (!data)
		return (EXIT_FAILURE);
	if (!arg || (arg->data && arg->data[0] == '\0'))
		return (EXIT_SUCCESS);
	if (!ft_strcmp(arg->data, "PWD"))
	{
		modif_env(data, arg->data, "");
		hide_env(data, arg->data);
	}
	else
		delete_env(data, arg->data);
	return (EXIT_SUCCESS);
}
