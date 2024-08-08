/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:41 by algultse          #+#    #+#             */
/*   Updated: 2024/08/08 17:17:08 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_digit(t_data *data, cmd_node *arg)
{
	char			*res_arg;
	char			*arg_cpy;
	long long int	i;

	arg_cpy = ft_strdup_m(data->m, arg->data);
	if (arg_cpy[0] == '+')
		arg_cpy++;
	i = ft_atoi_long_long_int(arg_cpy);
	res_arg = ft_itoa_long_long_int_m(data->m, i);
	if (ft_strcmp(arg_cpy, res_arg) != 0)
	{
		data->exit_code = EXIT_ERR_DIGIT;
		return (ft_free(data->m, res_arg), ft_free(data->m, arg_cpy), \
		ft_strerror(data, "exit", arg->data, "numeric argument required"), false);
	}
	ft_free(data->m, res_arg);
	ft_free(data->m, arg_cpy);
	if (i > EXIT_CODE_MODULO || i < -EXIT_CODE_MODULO)
		data->exit_code = (i % EXIT_CODE_MODULO);
	else if (i < 0)
		data->exit_code = EXIT_CODE_MODULO + (i);
	else
		data->exit_code = i;
	return (true);
}

void	check_exit_arg(t_data *data, cmd_node *arg, bool *do_exit)
{
	if (!data || !arg)
		return ;
	if (!check_digit(data, arg))
		return ;
	if (arg->right)
	{
		*do_exit = false;
		data->exit_code = EXIT_FAILURE;
		ft_strerror(data, "exit", NULL, "too many arguments");
	}
}

void	close_everything(t_data *data)
{
	if (!data)
		return ;
	if (data->out_fd != -1)
		close(data->out_fd);
	if (data->in_fd != -1)
		close(data->in_fd);
	if (data->fds.out != -1)
		close(data->fds.out);
	if (data->fds.in != -1)
		close(data->fds.in);
	if (data->fds.no != -1)
		close(data->fds.no);
	if (data->out_fd != STDOUT_FILENO && \
		data->fds.out != STDOUT_FILENO && data->fds.no != STDOUT_FILENO)
		close(STDOUT_FILENO);
	if (data->in_fd != STDIN_FILENO && \
		data->fds.in != STDIN_FILENO && data->fds.no != STDIN_FILENO)
		close(STDIN_FILENO);
	close(STDERR_FILENO);
}

void	exit_builtin(t_data *data, cmd_node *arg, bool display)
{
	int		exit_code;
	bool	do_exit;

	if (!data)
		exit(EXIT_FAILURE);
	if (display == true)
		write(STDERR_FILENO, "exit\n", 5);
	do_exit = true;
	check_exit_arg(data, arg, &do_exit);
	exit_code = data->exit_code;
	if (do_exit == false)
		return ;
	close_everything(data);
	// free_all_parsed(data->all_parsed, data->nb_cmds);
	ft_free_all(data->m);
	// rl_clear_history();
	exit(exit_code);
}