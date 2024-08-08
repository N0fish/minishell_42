/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:01:55 by algultse          #+#    #+#             */
/*   Updated: 2024/08/08 14:24:28 by algultse         ###   ########.fr       */
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

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	if (array)
	{
		free(array);
		array = NULL;
	}
}

// void	ft_free_t_cmd(t_data *data)
// {
// 	int			i;

// 	if (!data || !data->all_parsed)
// 		return ;
// 	i = 0;
// 	while (i < data->nb_cmds)
// 	{
// 		if (data->all_parsed[i].pipex)
// 			free_cmd(data, data->all_parsed[i].pipex);
// 		i++;
// 	}
// }

// void	ft_free_cmd(t_data *data)
// {
// 	int			i;

// 	if (!data || !data->all_parsed)
// 		return ;
// 	i = 0;
// 	while (i < data->nb_cmds)
// 	{
// 		if (data->all_parsed[i].pipex)
// 			free_cmd(data, data->all_parsed[i].pipex);
// 		i++;
// 	}
// }