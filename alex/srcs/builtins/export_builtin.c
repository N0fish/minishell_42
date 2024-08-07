/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:16:57 by algultse          #+#    #+#             */
/*   Updated: 2024/07/16 13:17:49 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_key_value(t_data *data, char *arg, char **res_key, char **res_value)
{
	char	*res;
	int		len_key;
	int		len_value;

	res = ft_strchr(arg, '=');
	if (!res)
	{
		len_key = ft_strlen(arg);
		*res_value = NULL;
	}
	else
	{
		len_key = res - arg;
		len_value = ft_strlen(arg) - len_key - 1;
		*res_value = (char *)ft_malloc(data->m, sizeof(char) * (len_value + 1));
		ft_strlcpy(*res_value, arg + len_key + 1, len_value + 1);
	}
	*res_key = (char *)ft_malloc(data->m, sizeof(char) * (len_key + 1));
	ft_strlcpy(*res_key, arg, len_key + 1);
	return (EXIT_SUCCESS);
}

void	update_env(t_data *data, char *res_key, char *res_value)
{
	t_envp	*list;

	list = seek_env(data->envp, res_key);
	if (list)
	{
		modif_env(data, res_key, res_value);
		list->display = true;
		ft_free(data->m, res_key);
		if (res_value)
			ft_free(data->m, res_value);
	}
	else
		add_env(data, res_key, res_value);
}

int	export_builtin_update(t_data *data, char **cmd)
{
	char	*key;
	char	*value;
	int		exit;

	if (!cmd && !*cmd)
		return (EXIT_FAILURE);
	exit = EXIT_SUCCESS;
	while (*cmd)
	{
		if (parse_key_value(data, *cmd, &key, &value) == EXIT_SUCCESS)
		{
			if (!ft_isstralnum(key))
			{
				ft_strerror_q(data, "export", *cmd, INVALID_ID);
				exit = EXIT_FAILURE;
			}
			else
				update_env(data, key, value);
		}
		ft_free(data->m, key);
		if (value)
			ft_free(data->m, value);
		cmd++;
	}
	return (exit);
}

int	export_builtin(t_data *data, char **cmd)
{
	if (!data)
		return (EXIT_FAILURE);
	if (cmd && !cmd[1])
		return (declare_env_builtin(data));
	cmd++;
	return (export_builtin_update(data, cmd));
}
