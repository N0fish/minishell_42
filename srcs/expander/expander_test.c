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

// #include "expander.h"
// #include "minishell.h"

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
	if (!dollar)
		return (0);
	if (dollar[0] == '$')
		dollar++;
	if (dollar[0] == '?')
		return (2);
	while (dollar[len] && (ft_isascii(dollar[len]) && dollar[len] != ' ' && dollar[len] != '$'))
		len++;
	return (len + 1);
}

static char	*replace_dollar_by(t_malloc *m, char *str, char *var)
{
	char	*new_str;
	char	*tmp;
	char	*tmp2;
	int		len;
	int		new_len;

	len = get_length_var(str);
	new_len = (int)ft_strlen(str) - len + (int)ft_strlen(var);
	new_str = malloc(new_len + 1);
	ft_strlcpy(new_str, str, ft_strlen(str) - len + 1);
	tmp = ft_strnstr(str, "$", ft_strlen(str));
	if (str)
		free(str);
	tmp2 = ft_strjoin_m(m, var, tmp + len);
	ft_free(m, var);
	ft_strlcpy(new_str + ft_strlen(new_str), tmp2, ft_strlen(tmp2) + 1);
	ft_free(m, tmp2);
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
	{
		res = replace_dollar_by(data->m, str, \
			ft_itoa_m(data->m, data->exit_code));
		return (res);
	}
	else
	{
		var = ft_substr_m(data->m, dollar, 0, var_len - 1);
		printf("var: %s\n", var);
		printf("len = %d\n", (int)ft_strlen(var));
		value = seek_env_value(data->envp, var);
		ft_free(data->m, var);
		if (value)
			res = replace_dollar_by(data->m, str, ft_strdup_m(data->m, value));
		else
			res = replace_dollar_by(data->m, str, ft_strdup_m(data->m, "2"));
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
		dollar = get_dollar_pos(str);
	}
	return (str);
}
