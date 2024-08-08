/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:48 by algultse          #+#    #+#             */
/*   Updated: 2024/08/08 18:11:09 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd_path(t_malloc *m, char **paths, char *cmd)
{
	char	*tmp;
	char	*res_cmd;

	while (*paths)
	{
		tmp = ft_strjoin_m(m, *paths, "/");
		if (!tmp)
			return (NULL);
		res_cmd = ft_strjoin_m(m, tmp, cmd);
		ft_free(m, tmp);
		if (!res_cmd)
			return (NULL);
		if (access(res_cmd, 0) == 0)
			return (res_cmd);
		ft_free(m, res_cmd);
		paths++;
	}
	return (ft_strdup_m(m, cmd));
}

char	**split_cmd_argv(t_data *data, char **cmd_args, \
							char **res_path, char **data_cmd)
{
	char	*cmd;
	char	*tmp;

	if (!cmd_args)
		return (NULL);
	if (data_cmd)
		*data_cmd = find_cmd_path(data->m, res_path, cmd_args[0]);
	ft_free_array(data->m, (void **)res_path);
	cmd = ft_strrchr(cmd_args[0], '/');
	if (!cmd)
		return (cmd_args);
	if (cmd[ft_strlen(cmd) -1] == '/')
		tmp = ft_strdup_m(data->m, cmd_args[0]);
	else
		tmp = ft_strdup_m(data->m, cmd + 1);
	free(cmd_args[0]);
	cmd_args[0] = tmp;
	return (cmd_args);
}

bool	is_directory(char *path, bool slash)
{
	struct stat	path_stat;

	if (slash && path[0] != '/')
		return (false);
	ft_memset(&path_stat, 0, sizeof(struct stat));
	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

t_cmd	*prepare_cmd(t_data *data, cmd_node *node)
{
	char	*cmd;
	char	**args;
	t_cmd	*cmd_res;
	char	*path;
	int		argc;

	(void) path;
	cmd = NULL;
	(void) cmd;

	if (!data || !node)
		return (NULL);
	cmd_res = (t_cmd *)ft_malloc(data->m, sizeof(t_cmd));
	path = seek_env_value(data->envp, "PATH");
	if (!node->data)
		path = "";
	if (is_directory(node->data, true))
	{
		data->exit_code = ERROR_CMD_NOT_EXET;
		return (ft_strerror(data, NULL, node->data, "Is a directory"), NULL);
	}
	args = get_command_args(node, &argc);
	args = split_cmd_argv(data, args, \
				ft_split_m(data->m, path, ':'), &cmd);
	cmd_res->cmd = cmd;
	cmd_res->args = args;
	cmd_res->pipes = (int *) ft_malloc(data->m, sizeof(int) * 2);
	cmd_res->pipes[0] = -1;
	cmd_res->pipes[1] = -1;
	return (cmd_res);
}

t_cmd	*pid_only_cmd(t_malloc *m, pid_t pid)
{
	t_cmd	*cmd;

	if (!m)
		return (NULL);
	cmd = (t_cmd *)ft_malloc(m, sizeof(t_cmd));
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->pid = pid;
	cmd->pipes = (int *) ft_malloc(m, sizeof(int) * 2);
	cmd->pipes[0] = -1;
	cmd->pipes[1] = -1;
	return (cmd);
}
