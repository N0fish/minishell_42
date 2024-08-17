/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:32:54 by alex              #+#    #+#             */
/*   Updated: 2024/08/17 12:26:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"

char	*get_dollar_pos(char *str)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '$')
			return (str);
		str++;
	}
	return (NULL);
}

int	get_length_var(char *str)
{
	int		len;
	char	*dollar;

	len = 0;
	dollar = get_dollar_pos(str);
	if (dollar[0] == '$')
		dollar++;
	if (dollar[0] == '?')
		return (2);
	while (dollar[len] && (ft_isascii(dollar[len]) && dollar[len] != ' '))
		len++;
	return (len+1);
}

static char	*replace_dollar_by(t_malloc *m, char *str, char *var)
{
	char	*new_str;
	char	*tmp;
	char	*tmp2;
	int		len;

	len = get_length_var(str);
	new_str = ft_strdup_m(m, str);
	tmp = ft_strnstr(new_str, "$", ft_strlen(new_str));
	tmp2 = ft_strjoin_m(m, var, tmp + len);
	ft_strlcpy(tmp, tmp2, ft_strlen(tmp2) + 1);
	return (new_str);
}

static char	*check_var(t_data *data, char *str)
{
	char	*dollar;
	char	*var;
	char	*value;
	int		var_len;

	if (!str)
		return (NULL);
	dollar = get_dollar_pos(str);
	var_len = get_length_var(dollar);
	if (!dollar)
		return (str);
	if (dollar[0] == '$')
		dollar++;
	if (dollar[0] == '?')
		return (replace_dollar_by(data->m, str,
				ft_itoa_m(data->m, data->exit_code)));
	else
	{
		var = ft_substr(dollar, 0, var_len);
		printf("var: %s\n", var);
		value = seek_env_value(data->envp, var);
		printf("value: %s\n", value);
		// если раскоментить падает minishell
		// printf("value: %s\n", replace_dollar_by(data->m, str, value));
		return (replace_dollar_by(data->m, str, "2"));
	}
	return (str);
}

char	*check_vars(t_data *data, char *str)
{
	char	*dollar;

	if (!str)
		return (NULL);
	dollar = get_dollar_pos(str);
	while (dollar)
	{
		str = check_var(data, str);
		dollar = get_dollar_pos(str);
	}
	return (str);
}
