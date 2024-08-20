/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:28 by algultse          #+#    #+#             */
/*   Updated: 2024/08/20 19:05:23 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*find_key_pos(char *str, int *len)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	len[0] = -1;
	len[1] = -1;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	if (str[i] == '\0')
		return (NULL);
	len[0] = i;
	while (str[i] != '\0' && str[i + 1] != '\0' \
		&& str[i] != '?' \
		&& (str[i + 1] != ' ' && !(str[i + 1] >= '\t' && str[i + 1] <= '\r')))
		i++;
	len[1] = i;
	if (len[0] == len[1])
		return (NULL);
	return (len);
}

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
	else
		return (ft_strdup_m(data->m, ""));
}

char	*process_key(t_data *data, char *line, \
					int len_key[2], char **start_line)
{
	char	*key;
	char	*value;
	char	*res_str;

	if (!data || !line)
		return (NULL);
	key = seek_key_in_str(data, line, len_key);
	value = seek_env_or_exit_code(data, key);
	ft_free(data->m, key);
	res_str = replace_key_to_value(line, len_key, value);
	if (res_str)
	{
		free(line);
		line = res_str;
		*start_line = line + len_key[0] + ft_strlen(value);
		ft_free(data->m, value);
	}
	return (line);
}
