/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:53:12 by alex              #+#    #+#             */
/*   Updated: 2024/08/20 18:58:18 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_fds
{
	int	in;
	int	out;
	int	no;
	int	pipe[2];
}				t_fds;

typedef struct s_envp
{
	char			*key;
	char			*value;
	bool			display;
	struct s_envp	*prev;
	struct s_envp	*next;
}				t_envp;

typedef struct s_data
{
	struct s_malloc	*m;
	struct s_envp	*envp;
	int				exit_code;
	char			*shell_name;
	bool			here_doc;
	int				wtpd;
	bool			exec_error;
	int				out_fd;
	int				in_fd;
	struct s_fds	fds;
	struct cmd_node	*entry_node;
}				t_data;

typedef struct s_ms_pids
{
	pid_t	pids[1024];
	int		it;
}				t_ms_pids;

// INIT
// env_init
bool	copy_env(t_data *data, char **envp);
// env_prepare
void	prepare_shlvl(t_data *data);
void	prepare_path(t_data *data);
void	prepare_oldpwd(t_data *data);
bool	prepare_env(t_data *data, char **argv);
// env_utils
t_envp	*empty_block(t_data *data);
void	modif_or_add_env(t_data *data, char *key, char *value);
void	delete_env(t_data *data, char *key);
void	hide_env(t_data *data, char *key);
size_t	env_len(t_envp *envp, bool has_display);
// env
t_envp	*seek_env(t_envp *envp, char *key);
char	*seek_env_value(t_envp *envp, char *name);
int		modif_env(t_data *data, char *key, char *value);
bool	add_env(t_data *data, char *key, char *value);
// init
t_envp	*new_env_block(t_data *data, char **envp);
t_data	*init(char **argv, char **envp);

#endif