/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:01:55 by algultse          #+#    #+#             */
/*   Updated: 2024/08/09 23:44:48 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_data *data, t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
	{
		ft_free_array(data->m, (void **)cmd->args);
		cmd->args = NULL;
	}
	if (cmd->cmd)
	{
		ft_free(data->m, cmd->cmd);
		cmd->cmd = NULL;
	}
	ft_free(data->m, cmd);
	cmd = NULL;
}
