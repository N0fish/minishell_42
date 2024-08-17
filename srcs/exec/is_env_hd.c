/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_env_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:28 by algultse          #+#    #+#             */
/*   Updated: 2024/07/16 13:23:42 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int *find_key_pos(char *str, int *len)
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
		&& str[i] != '?' && str[i + 1] != '$' \
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

char    *process_key(t_data *data, char *line, int *len_key, char **start_line)
{
	char	*key;
	char	*value;
	char	*res_str;
	int		flag;

	if (!data || !line)
		return (NULL);
	flag = 0;
	key = seek_key_in_str(data, line, len_key);
	value = seek_env_value(data->envp, key);
	if (key)
		ft_free(data->m, key);
	if (!value)
	{
		value = ft_strdup_m(data->m, "");
		flag = 1;
	}
	res_str = replace_key_to_value(line, len_key, value);
	if (res_str)
	{
		free(line);
		*start_line = line + len_key[0] + ft_strlen(value);
		if (value && flag == 1)
			ft_free(data->m, value);	
	}
	return (res_str);
}

char	*is_there_env(t_data *data, char *line)
{
	char	*start_line;
	int		len_key[2];

	if (!data || !line)
		return (NULL);
	start_line = line;
	while (*start_line != '\0')
	{
		find_key_pos(line, len_key);
		if (len_key[0] != -1)
		{
			line = process_key(data, line, len_key, &start_line);
			if (!line)
				break ;
		}
		else
			break ;
	}
	return (line);
}

// int	main()
// {
// 	char	*line;
// 	char	*start;
// 	char	*key;
// 	int		len_key[2];
// 	char	*res_str;
// 	char	*value;

// 	key = NULL;
// 	line = strdup("ca $PWD va $GRT");
// 	res_str = NULL;
// 	start = line;
// 	while (*start != '\0')
// 	{
// 		find_key_pos(line, len_key);
// 		if (len_key[0] != -1)
// 		{
// 			key = seek_key_in_str(line, len_key);
// 			if (!key)
// 				return (1);
// 			// value = seek_env_value(data->envp, key);
// 			value = strdup("/home/str");
// 			if (!value)
// 				value = strdup("");
// 			else if (key)
// 			{
// 				free (key);
// 				key = NULL;
// 			}
// 			res_str = replace_key_to_value(line, len_key, value);
// 			if (res_str)
// 			{
// 				if (line)
// 					free(line);
// 				if (value)
// 					free(value);
// 				line = res_str;
// 				start = line + len_key[0] + strlen(value);	
// 			}
// 		}
// 		else
// 			break ;
// 	}
// }
