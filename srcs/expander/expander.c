/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:41:01 by alex              #+#    #+#             */
/*   Updated: 2024/08/14 13:32:18 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char    *get_dollar_pos(char *str)
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

static int		get_length_var(char *str)
{
	int		len;
	char 	*dollar;

	len = 0;
	dollar = get_dollar_pos(str);
	if (dollar[0] == '$')
		dollar++;
	while (dollar[len] && (ft_isalnum(dollar[len]) || dollar[len] == '?'))
		len++;
	return (len + 1);
}

char		*replace_dollar_by(char *str, char *var)
{
	char	*new_str;
	char	*tmp;
	char	*tmp2;
	int		len;

	len = get_length_var(str);
	new_str = ft_strdup(str);
	tmp = ft_strnstr(new_str, "$", ft_strlen(new_str));
	tmp2 = ft_strjoin(var, tmp + len);
	ft_strlcpy(tmp, tmp2, ft_strlen(tmp2) + 1);
	free(tmp2);
	return (new_str);
}

char	*check_var(t_data *data, char *str)
{
	char *dollar;

	if (!str)
		return (NULL);

	dollar = get_dollar_pos(str);
	if (!dollar)
		return (str);
	if (dollar[0] == '$')
		dollar++;
	if (dollar[0] == '?')
		return (replace_dollar_by(str, ft_itoa(data->exit_code)));
	else
		return (replace_dollar_by(str, "42"));
	return (str);
}

cmd_node *expander(t_data *data, cmd_node *node)
{
	if (!data || !node)
		return NULL;

	cmd_node *head = node;

	while (node)
	{
		if (node->type == NODE_DQ_ARGUMENT || node->type == NODE_ARGUMENT)
		{
			node->data = check_var(data, node->data);
			node->type = NODE_ARGUMENT;
		}
		else if (node->type == NODE_Q_ARGUMENT)
			node->type = NODE_ARGUMENT;
		else if (node->type == NODE_PIPE)
		{
			node->left = expander(data, node->left);
			node->right = expander(data, node->right);
		}
		else if (node->type == NODE_REDIRECT_IN || node->type == NODE_REDIRECT_OUT)
		{
			node->left = expander(data, node->left);
		}
		node = node->right;
	}
	return (head);
}
