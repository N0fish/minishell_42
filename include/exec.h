/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:03 by algultse          #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
}				t_cmd;

// EXEC
// command
char	**get_command_args(t_data *data, t_cmd_node *node);
// exec
int		exec_entry(t_data *data, t_cmd_node *node);
// fds_utils
bool	fds_ok(t_fds fds);
int		find_final_fd(t_data *data, t_cmd_node **red, \
						int node_type, int open_modes[2]);
void	close_fds(t_fds fds);
void	close_child_fds(t_fds fds);
// fds
t_fds	init_fds(t_fds io);
t_fds	update_fds(t_fds fds, t_fds io);
t_fds	end_update_fds(t_fds fds, t_fds io);
t_fds	in_out(t_data *data, t_cmd_node *node);

int		*find_key_pos(char *str, int *len, int i);
// parsed_utils
bool	is_directory(char *path, bool slash);
t_cmd	*prepare_cmd(t_data *data, t_cmd_node *node);
bool	try_dir_or_file(char *path);
// pids
pid_t	exec_child(t_data *data, t_fds fds, t_cmd *cmd, char **envp);
void	add_pid(t_ms_pids *pids, pid_t pid);
void	wait_pids(t_data *data, t_ms_pids pids);

#endif