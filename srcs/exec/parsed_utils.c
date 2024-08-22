/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:23:48 by algultse          #+#    #+#             */
/*   Updated: 2024/08/22 18:10:39 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_cmd_path(t_malloc *m, char **paths, char *cmd)
{
	char	*tmp;
	char	*res_cmd;

	if (try_dir_or_file(cmd) || *cmd == '\0')
		return (ft_strdup_m(m, cmd));
	while (paths && *paths)
	{
		tmp = ft_strjoin_m(m, *paths, "/");
		if (!tmp)
			return (NULL);
		res_cmd = ft_strjoin_m(m, tmp, cmd);
		ft_free(m, tmp);
		if (!res_cmd)
			return (NULL);
		if (access(res_cmd, F_OK) == 0)
			return (res_cmd);
		ft_free(m, res_cmd);
		paths++;
	}
	return (ft_strdup_m(m, cmd));
}

char	**split_cmd_argv(t_data *data, char **cmd_args, \
							char **paths, char **data_cmd)
{
	char	*cmd;
	char	*tmp;

	if (!cmd_args || !cmd_args[0])
		return (NULL);
	if (data_cmd)
		*data_cmd = find_cmd_path(data->m, paths, cmd_args[0]);
	ft_free_array(data->m, (void **)paths);
	cmd = ft_strrchr(cmd_args[0], '/');
	if (!cmd)
		return (cmd_args);
	if (cmd[ft_strlen(cmd) -1] == '/')
		tmp = ft_strdup_m(data->m, cmd_args[0]);
	else
		tmp = ft_strdup_m(data->m, cmd + 1);
	ft_free(data->m, cmd_args[0]);
	cmd_args[0] = tmp;
	return (cmd_args);
}

bool	is_directory(char *path, bool slash)
{
	struct stat	path_stat;

	if ((slash && path && path[0] != '/') || !path || (path && path[0] == 0))
		return (false);
	ft_memset(&path_stat, 0, sizeof(struct stat));
	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}

bool	try_dir_or_file(char *path)
{
	return (path && (path[0] == '/' || ft_strncmp(path, "./", 2) == 0));
}

t_cmd	*prepare_cmd(t_data *data, t_cmd_node *node)
{
	char	*cmd;
	char	**args;
	t_cmd	*cmd_res;
	char	*path;

	cmd = NULL;
	cmd_res = (t_cmd *)ft_malloc(data->m, sizeof(t_cmd));
	path = seek_env_value(data->envp, "PATH");
	if (!node->data)
		path = "";
	if (is_directory(node->data, true))
	{
		data->exit_code = ERROR_CMD_NOT_EXET;
		return (ft_strerror(data, NULL, node->data, "Is a directory"), NULL);
	}
	args = get_command_args(data, node);
	if (!args || !args[0])
		return (NULL);
	args = split_cmd_argv(data, args, ft_split_m(data->m, path, ':'), &cmd);
	if (!args)
		return (NULL);
	cmd_res->cmd = cmd;
	cmd_res->args = args;
	return (cmd_res);
}
