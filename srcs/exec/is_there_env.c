/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:28 by algultse          #+#    #+#             */
/*   Updated: 2024/08/21 15:04:27 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*seek_key_in_str(t_data *data, char *str, int *res)
{
	char	*key;
	size_t	key_len;

	if (!data || !str)
		return (NULL);
	key_len = res[1] - res[0];
	key = ft_malloc(data->m, key_len + 1);
	ft_strncpy(key, str + res[0] + 1, key_len);
	key[key_len] = '\0';
	return (key);
}

char	*replace_key_to_value(char *str, int *res, const char *value)
{
	int		orig_len;
	int		val_len;
	int		new_len;
	char	*new_str;

	if (!str)
		return (NULL);
	orig_len = ft_strlen(str);
	val_len = ft_strlen(value);
	new_len = orig_len - (res[1] - res[0] + 1) + val_len;
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, res[0]);
	new_str[res[0]] = '\0';
	ft_strcat(new_str, value);
	ft_strcat(new_str, str + res[1] + 1);
	return (new_str);
}

char	*seek_env_or_exit_code(t_data *data, char *key)
{
	char	*value;

	if (!data || !key)
		return (NULL);
	if (*key == '?')
		return (ft_itoa_m(data->m, data->exit_code));
	if (*key == '$')
		return (ft_strdup_m(data->m, ""));
	value = seek_env_value(data->envp, key);
	if (value)
		return (ft_strdup_m(data->m, value));
	return (NULL);
}

char	*remove_dol(char *line, int *pos)
{
	int		future_len;
	char	*new;
	int		it;

	if (!line || !ft_strlen(line))
		return (NULL);
	future_len = ft_strlen(line) - (pos[1] - pos[0] + 1);
	if (!future_len)
		return (free(line), NULL);
	new = (char *)malloc(future_len + 1);
	it = -1;
	if (!new)
		return (line);
	while (++it < pos[0])
		new[it] = line[it];
	while (it < future_len)
	{
		new[it] = line[pos[1] - pos[0] + it + 1];
		it++;
	}
	new[it] = 0;
	free(line);
	return (new);
}

char	*is_there_env(t_data *data, char *line)
{
	int		len_key[2];
	char	*tmp;
	int		diff;

	if (!data || !line)
		return (NULL);
	if (!ft_strlen(line))
		return (line);
	diff = 0;
	while (line && diff < (int)ft_strlen(line))
	{
		find_key_pos(line, len_key, diff);
		if (len_key[0] == -1 || len_key[1] == -1)
			break ;
		if (len_key[0] == len_key[1] && ++diff)
			continue ;
		tmp = process_key(data, line, len_key, &diff);
		if (!tmp)
			line = remove_dol(line, len_key);
		else
			line = tmp;
	}
	return (line);
}
