/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:02:02 by algultse          #+#    #+#             */
/*   Updated: 2024/07/29 13:05:04 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin_utils(t_data *data)
{
	char	*new_pwd;
	int		exit;

	exit = EXIT_SUCCESS;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		ft_strerror(data, "cd", "error retrieving current directory", \
				"getcwd: cannot access parent directories");
		return (EXIT_FAILURE);
	}
	exit = modif_env(data, "PWD", new_pwd);
	free(new_pwd);
	return (exit);
}

int	see_args(t_data *data, char **cmd)
{
	if (!data || !cmd)
		return (EXIT_FAILURE);
	if (cmd[1] && cmd[1][0] == '-')
		return (ft_strerror(data, "cd", cmd[1], "invalid option"), \
				EXIT_INVALID_OPERATION);
	else if (cmd[1] && cmd[2])
		return (ft_strerror(data, "cd", NULL, "too many arguments"), \
				EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	cd_builtin(t_data *data, char *path, char **cmd)
{
	t_envp	*oldpwd;
	t_envp	*pwd;

	if (!data)
		return (EXIT_FAILURE);
	if ((cmd[1] && cmd[1][0] == '-') || (cmd[1] && cmd[2]))
		return (see_args(data, cmd));
	if (!path)
	{
		path = seek_env_value(data->envp, "HOME");
		if (!path)
			return (ft_strerror(data, "cd", NULL, "HOME not set"), \
					EXIT_FAILURE);
	}
	oldpwd = seek_env(data->envp, "OLDPWD");
	pwd = seek_env(data->envp, "PWD");
	if (oldpwd)
	{
		modif_or_add_env(data, "OLDPWD", pwd->value);
		oldpwd->display = true;
	}
	if (chdir(path) != 0)
		return (ft_strerror(data, "cd", path, strerror(errno)), EXIT_FAILURE);
	return (cd_builtin_utils(data));
}
