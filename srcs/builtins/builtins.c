/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:13 by algultse          #+#    #+#             */
/*   Updated: 2024/08/08 22:48:20 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_builtins(char **argv, char **envp)
{
	t_data	*data;

	data = init(argv, envp);
	if (!data)
		exit(EXIT_FAILURE);
	return (data);
}

void	exec_builtin(t_data *data, cmd_node *cmd)
{
	if (!data || !cmd || !cmd->data)
		return ;
	if (!ft_strcmp(cmd->data, "pwd"))
		data->exit_code = pwd_builtin(data);
	else if (!ft_strcmp(cmd->data, "cd"))
		data->exit_code = cd_builtin(data, cmd->right);
	else if (!ft_strcmp(cmd->data, "unset"))
		data->exit_code = unset_builtin(data, cmd->right);
	else if (!ft_strcmp(cmd->data, "env"))
		data->exit_code = env_builtin(data);
	else if (!ft_strcmp(cmd->data, "export"))
		data->exit_code = export_builtin(data, cmd->right);
	else if (!ft_strcmp(cmd->data, "echo"))
		data->exit_code = echo_builtin(data, cmd->right);
	else if (!ft_strcmp(cmd->data, "exit"))
		exit_builtin(data, cmd->right, true);
}

bool	use_builtin_close(t_data *data)
{
	if (!data)
		return (false);
	// if (data->out_fd != -1)
	// {
	// 	close(data->out_fd);
	// 	data->out_fd = -1;
	// }
	// if (data->in_fd != -1)
	// {
	// 	close(data->in_fd);
	// 	data->in_fd = -1;
	// }
	return (true);
}

bool	use_builtin(t_data *data, cmd_node *cmd, t_fds fds)
{
	int out;
	int in;

	if (!data || !cmd)
		return (false);
	if (!ft_match_any(data, cmd->data, \
		"pwd,cd,unset,env,export,echo,exit"))
		return (false);
	out = dup(STDOUT_FILENO);
	in = dup(STDIN_FILENO);
	if (out < 0 || in < 0 || \
		dup2(fds.out, STDOUT_FILENO) < 0 || \
		dup2(fds.in, STDIN_FILENO) < 0)
		return (true);
	exec_builtin(data, cmd);
	if (dup2(out, STDOUT_FILENO) < 0 || \
		dup2(in, STDIN_FILENO) < 0)
		return (true);
	return (use_builtin_close(data));
}

bool	fork_builtin(t_data *data, cmd_node *cmd, t_fds fds)
{
	pid_t	child;

	if (!ft_match_any(data, cmd->data, \
		"pwd,cd,unset,env,export,echo,exit"))
		return (false);
	if (fds.in == -1 || fds.out == -1)
	{
		data->exit_code = -1;
		return (-1);
	}
	child = fork();
	if (child < 0)
	{
		ft_strerror(data, "fork", NULL, strerror(errno));
		data->exit_code = -1;
		return (-1);
	}
	if (child == 0)
	{
		dup2(fds.in, STDIN_FILENO);
		dup2(fds.out, STDOUT_FILENO);
		use_builtin(data, cmd, fds);
		if (fds.no != -1 && fds.no != fds.in && fds.no != fds.out)
			close(fds.no);
		exit_builtin(data, NULL, false);
	}
	data->exec_error = waitpid(child, &data->wtpd, 0) == -1;
	printf("fork_builtin > fds.in: %d, fds.out: %d\n", fds.in, fds.out);
	if (fds.in != STDIN_FILENO && fds.in != -1)
		close(fds.in);
	if (fds.out != STDOUT_FILENO && fds.out != -1)
		close(fds.out);
	return (true);
}