/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:03 by algultse          #+#    #+#             */
/*   Updated: 2024/07/21 19:59:33 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*new_env_block(t_data *data, char **envp)
{
	int		v_len;
	char	*value;
	t_envp	*tmp;

	if (!data)
		return (NULL);
	tmp = empty_block(data);
	if (!tmp || !envp || !*envp)
		return (tmp);
	value = ft_strchr(*envp, '=');
	v_len = ft_strlen(value);
	if (value && value != 0)
		value++;
	tmp->value = ft_strdup_m(data->m, value);
	if (!tmp->value)
		return (NULL);
	tmp->key = ft_substr_m(data->m, *envp, 0, ft_strlen(*envp) - (size_t)v_len);
	if (!tmp->key)
		return (NULL);
	tmp->display = true;
	return (tmp);
}

char	*get_shell_name(char **argv)
{
	if (*argv && !ft_strncmp("./", *argv, 2))
		return (*argv + 2);
	return (*argv);
}

void	init_vars(t_data *data, char **argv)
{
	if (!data)
		return ;
	data->shell_name = get_shell_name(argv);
	data->exit_code = EXIT_SUCCESS;
	data->wtpd = -1;
	data->exec_error = false;
	data->all_parsed = NULL;
	data->nb_cmds = 0;
	data->out_fd = -1;
	data->in_fd = -1;
	data->forks = 0;
	data->fds = (t_fds){\
		.in = -1, \
		.out = -1, \
		.no = -1 \
	};
}

t_data	*init(char **argv, char **envp)
{
	t_data		*data;
	t_malloc	*m;

	m = init_malloc();
	if (!m)
		return (NULL);
	data = (t_data *)ft_malloc(m, sizeof(t_data));
	if (!data)
		return (ft_free_all(m), NULL);
	data->m = m;
	if (!copy_env(data, envp) || !prepare_env(data, argv))
		return (ft_free_all(m), NULL);
	init_vars(data, argv);
	return (data);
}
