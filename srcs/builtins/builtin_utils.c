/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:03 by algultse          #+#    #+#             */
/*   Updated: 2024/08/08 16:43:42 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isstralnum(char *str)
{
	if (!ft_isalpha(*str) && *str != '=' && *str != '_')
		return (false);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		str++;
	}
	return (true);
}

bool	ft_match_any(t_data *data, char *str, char *any)
{
	char	**arr;
	int		i;

	if (!data || !str || !any)
		return (false);
	arr = ft_split_m(data->m, any, ',');
	if (!arr)
		return (false);
	i = 0;
	while (arr[i])
	{
		if (!str || !arr[i])
			break ;
		if (!ft_strcmp(str, arr[i]))
			return (ft_free_array(data->m, (void **)arr), true);
		i++;
	}
	return (ft_free_array(data->m, (void **)arr), false);
}

char	*envp_line(t_malloc *m, t_envp *envp)
{
	char	*line;
	char	*tmp;

	if (!m || !envp)
		return (NULL);
	tmp = ft_strjoin_m(m, envp->key, "=");
	if (!tmp)
		return (NULL);
	line = ft_strjoin_m(m, tmp, envp->value);
	if (!line)
		return (ft_free(m, tmp), NULL);
	ft_free(m, tmp);
	return (line);
}

char	**transform_envp(t_malloc *m, t_envp *envp)
{
	size_t	len;
	char	**envp_res;
	size_t	i;

	if (!m || !envp)
		return (NULL);
	len = env_len(envp, true);
	envp_res = (char **)ft_malloc(m, sizeof(char *) * (len + 1));
	i = 0;
	while (i < len && envp)
	{
		if (envp->display == false && !ft_strcmp(envp->key, "PATH"))
		{
			envp = envp->next;
			continue ;
		}
		envp_res[i] = envp_line(m, envp);
		if (!envp_res[i])
			return (ft_free_array(m, (void **)envp_res), NULL);
		envp = envp->next;
		i++;
	}
	envp_res[i] = NULL;
	return (envp_res);
}

void	modif_display(t_envp *envp, char *key, bool display)
{
	t_envp	*tmp;

	if (!envp || !key)
		return ;
	tmp = seek_env(envp, key);
	tmp->display = display;
}
