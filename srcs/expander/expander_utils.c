/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 11:32:54 by alex              #+#    #+#             */
/*   Updated: 2024/08/18 14:06:26 by alex             ###   ########.fr       */
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
	return (len + 1);
}

static char	*replace_dollar_by(t_malloc *m, char *str, char *var)
{
	char	*new_str;
	char	*tmp;
	char	*tmp2;
	int		len;

	len = get_length_var(str);
	printf("len = [%d]\n", len);
	new_str = ft_strdup_m(m, str);
	printf("new_str: [%s]\n", new_str);
	tmp = ft_strnstr(new_str, "$", ft_strlen(new_str) - 1);
	printf("tmp: [%s]\n", tmp);
	tmp2 = ft_strjoin_m(m, var, tmp + len);
	printf("tmp2: [%s]\n", tmp2);
	ft_strlcpy(tmp, tmp2, ft_strlen(tmp2) + 1);
	return (new_str);
}

static char	*check_var(t_data *data, char *str)
{
	char	*dollar;
	char	*var;
	char	*value;
	int		var_len;
	char	*res;
	

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
		var = ft_substr(dollar, 0, var_len - 1);
		printf("var: %s\n", var);
		printf("len = %d\n", (int)ft_strlen(var));
		value = seek_env_value(data->envp, var);
		if (value)
			res = replace_dollar_by(data->m, str, value);
		else
			res = replace_dollar_by(data->m, str, "2");
		if (value)
			printf("res: [%s]\n", res);
		return (res);
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
		printf("str: [%s]\n", str);
		dollar = get_dollar_pos(str);
		printf("dollar: [%s]\n", dollar);
	}
	printf("ret str: [%s]\n", str);
	return (str);
}
