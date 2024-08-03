/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_prepare.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:18:34 by algultse          #+#    #+#             */
/*   Updated: 2024/07/22 12:17:03 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_shlvl(t_data *data)
{
	char	*sh_lvl_str;
	int		sh_lvl;

	sh_lvl = 0;
	sh_lvl_str = seek_env_value(data->envp, "SHLVL");
	if (sh_lvl_str)
		sh_lvl = ft_atoi(sh_lvl_str);
	sh_lvl++;
	sh_lvl_str = ft_itoa_m(data->m, sh_lvl);
	if (sh_lvl_str)
	{
		modif_or_add_env(data, "SHLVL", sh_lvl_str);
		ft_free(data->m, sh_lvl_str);
	}
}

void	prepare_path(t_data *data)
{
	char	*path;

	path = seek_env_value(data->envp, "PATH");
	if (path)
		return ;
	if (add_env(data, "PATH", "/usr/bin:/bin"))
		hide_env(data, "PATH");
}

void	prepare_oldpwd(t_data *data)
{
	char	*path;
	t_envp	*oldpwd;

	path = seek_env_value(data->envp, "OLDPWD");
	if (path)
		return ;
	add_env(data, "OLDPWD", "");
	oldpwd = seek_env(data->envp, "OLDPWD");
	oldpwd->display = false;
}

bool	prepare_env(t_data *data, char **argv)
{
	char	*cwd;

	cwd = getcwd_builtin(data);
	if (!cwd)
		return (false);
	modif_or_add_env(data, "PWD", cwd);
	ft_free(data->m, cwd);
	if (argv && *argv)
		modif_or_add_env(data, "_", argv[0]);
	prepare_shlvl(data);
	prepare_path(data);
	prepare_oldpwd(data);
	return (true);
}
