/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:21:40 by algultse          #+#    #+#             */
/*   Updated: 2024/07/21 20:01:06 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


pid_t	exec_child(t_data *data, t_fds fds, t_cmd *cmd, char **envp)
{
	pid_t		child;

	(void) data;
	if (fds.in == -1 || fds.out == -1)
		return (-1);
	child = fork();
	if (child == 0)
	{
		data->exit_code = 0;
		dup2(fds.in, STDIN_FILENO);
		dup2(fds.out, STDOUT_FILENO);
		if (fds.no >= 0 && fds.no != fds.in && fds.no != fds.out)
			close(fds.no);
		if (is_directory(cmd->cmd, false))
		{
			data->exit_code = EX_NOTFOUND;
			ft_strerror(data, NULL, cmd->cmd, "No such file or directory");
		}
		else
		{
			if (access(cmd->cmd, X_OK) != 0)
			{
				data->exit_code = EX_NOTFOUND;
				ft_strerror(NULL, NULL, cmd->cmd, "command not found");
			}
			else
				execve(cmd->cmd, cmd->args, envp);
		}
		exit_builtin(data, NULL, false);
		// if (fds.in != STDIN_FILENO && fds.in != -1)
		// 	close(fds.in);
		// if (fds.out != STDOUT_FILENO && fds.out != -1)
		// 	close(fds.out);
		// close(STDIN_FILENO);
		// close(STDOUT_FILENO);
	}
	return (child);
}

void	trigger_cmd(t_data *data, t_parsed *parsed, t_fds fds, char **envp)
{
	t_cmd	*cmd;

	parsed->pipex = NULL;
	if (!data || !parsed)
		return ;
	parsed->is_pid = false;
	if (parsed->eof && *parsed->eof)
	{
		parsed->is_pid = true;
		handle_heredoc(*parsed->eof, fds.out);
		return ;
	}
	modif_env(data, "_", parsed->cmd[0]);
	if (use_builtin(data, parsed, fds))
		return ;
	cmd = prepare_cmd(data, parsed);
	if (!cmd)
		return ;
	cmd->pid = exec_child(data, fds, cmd, envp);
	parsed->pipex = cmd;
	parsed->is_pid = true;
	parsed->pipex->pipes[0] = fds.no;
	parsed->pipex->pipes[1] = fds.out;
	data->forks++;
}

int	exec_2_plus(t_data *data, t_parsed **parsed, int pipe_fds[2], t_fds *fds)
{
	char	**envp;
	int		i;

	data->forks = 0;
	i = 1;
	envp = transform_envp(data->m, data->envp);
	if (data->nb_cmds > 1)
	{
		*fds = init_fds(pipe_fds, in_out(data, (*parsed[0])));
		if (!fds_ok(*fds))
			return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
		trigger_cmd(data, &(*parsed)[data->forks], *fds, envp);
	}
	while ((i < data->nb_cmds - 1) && (*parsed)[i].cmd)
	{
		*fds = update_fds(*fds, pipe_fds, \
			in_out(data, (*parsed)[i]));
		if (!fds_ok(*fds))
			return (ft_free_array(data->m, (void **)envp), EXIT_FAILURE);
		trigger_cmd(data, &(*parsed)[i], *fds, envp);
		i++;
	}
	return (ft_free_array(data->m, (void **)envp), EXIT_SUCCESS);
}

int	exec_cmds(t_data *data)
{
	int			pipe_fds[2];
	char		**envp;

	data->forks = 0;
	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	if (!data || !data->all_parsed)
		return (EXIT_FAILURE);
	if (exec_2_plus(data, &data->all_parsed, pipe_fds, &data->fds) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	envp = transform_envp(data->m, data->envp);
	if (data->forks - 1 < data->nb_cmds)
	{
		data->fds = end_update_fds(pipe_fds, in_out(data, data->all_parsed[data->nb_cmds -1]));
		if (!fds_ok(data->fds))
			return (EXIT_FAILURE);
		trigger_cmd(data, &data->all_parsed[data->nb_cmds -1], data->fds, envp);
		if (pipe_fds[0] != -1)
			close(pipe_fds[0]);
		// printf("exit_code: %d\n", data->exit_code);
		wait_clean_up(data->fds, data);
	}
	// printf("exit_code: %d\n", data->exit_code);
	ft_free_array(data->m, (void **)envp);
	return (data->exit_code);
}
