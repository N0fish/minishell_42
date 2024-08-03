/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:12:46 by algultse          #+#    #+#             */
/*   Updated: 2024/07/14 13:05:45 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getcwd_builtin(t_data *data)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	return (ft_strdup_m(data->m, cwd));
}

int	pwd_builtin(t_data *data)
{
	char	*cwd;

	cwd = getcwd_builtin(data);
	if (!cwd)
		return (EXIT_FAILURE);
	if (safe_write(data, "pwd", cwd, STDOUT_FILENO) == EXIT_FAILURE)
		return (ft_free(data->m, cwd), EXIT_FAILURE);
	if (safe_write(data, "pwd", "\n", STDOUT_FILENO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_free(data->m, cwd);
	return (EXIT_SUCCESS);
}
