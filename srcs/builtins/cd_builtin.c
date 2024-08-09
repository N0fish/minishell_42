/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:02:02 by algultse          #+#    #+#             */
/*   Updated: 2024/08/10 00:28:45 by algultse         ###   ########.fr       */
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

int	see_args(t_data *data, cmd_node *arg)
{
	if (!data || !arg)
		return (EXIT_FAILURE);
	if (arg->data && arg->data[0] == '-')
		return (ft_strerror(data, "cd", arg->data, "invalid option"), \
				EXIT_INVALID_OPERATION);
	else if (arg->data && arg->right && arg->right->data)
		return (ft_strerror(data, "cd", NULL, "too many arguments"), \
				EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char *cd_no_data(t_data *data, cmd_node *cmd)
{
	char	*path;

	if (cmd && cmd->data)
		return (cmd->data);
	path = seek_env_value(data->envp, "HOME");
	if (!path)
		return (ft_strerror(data, "cd", NULL, "HOME not set"), \
				NULL);
	return (path);
}

int	cd_builtin(t_data *data, cmd_node *arg)
{
	t_envp	*oldpwd;
	t_envp	*pwd;
	char	*path;

	if (!data)
		return (EXIT_FAILURE);
	if (arg && ((arg->data && arg->data[0] == '-') \
		|| (arg->data && arg->right && arg->right->data)))
		return (see_args(data, arg));
	path = cd_no_data(data, arg);
	if (!path)
		return (EXIT_FAILURE);
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
