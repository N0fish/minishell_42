#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <stdbool.h>
# include "libft.h"
# include "ft_malloc.h"
# include "macros.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"

typedef struct s_fds {
	int	in;
	int	out;
	int	no;
}				t_fds;

typedef struct s_envp {
	char			*key;
	char			*value;
	bool			display;
	struct s_envp	*prev;
	struct s_envp	*next;
}				t_envp;

typedef struct s_cmd {
	char			*cmd;
	char			**args;
	int				*pipes;
	pid_t			pid;
}				t_cmd;

typedef struct s_data
{
	t_malloc		*m;
	struct s_envp	*envp;
	int				exit_code;
	char			*shell_name;
	bool			here_doc;
	int				wtpd;
	bool			exec_error;
	int				out_fd;
	int				in_fd;
	struct s_fds	fds;
	int				forks;
}				t_data;

// BUILTINS
// builtin_utils
bool	ft_isstralnum(char *str);
bool	ft_match_any(t_data *data, char *str, char *any);
char	**transform_envp(t_malloc *m, t_envp *envp);
void	modif_display(t_envp *envp, char *key, bool display);

// builtins
t_data	*init_builtins(char **argv, char **envp);
bool	use_builtin(t_data *data, cmd_node *node, t_fds fds);

// cd_builtin
int		cd_builtin(t_data *data, char *path, char **cmd);

// echo_builtin
int		echo_builtin(t_data *data, char **arg);

// env_builtin
int		env_builtin(t_data *data);

// exit_builtin
void	exit_builtin(t_data *data, char **arg, bool display);
void	close_everything(t_data *data);

// export_builtin_utils
int		declare_env_builtin(t_data *data);

// export_builtin
int		export_builtin(t_data *data, char **cmd);

// pwd_builtin
char	*getcwd_builtin(t_data *data);
int		pwd_builtin(t_data *data);

// unset_builtin
int		unset_builtin(t_data *data, char *key);

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

// EXEC_CMD
// exec
int		exec_cmds(t_data *data, cmd_node *cmd);

// fds_utils
int		path_to_fd(t_data *data, char *path, bool chev_left, bool right_append);
bool	fds_ok(t_fds fds);

// fds
t_fds	init_fds(int pipe_fds[2], t_fds io);
t_fds	update_fds(t_fds fds, int pipe_fds[2], t_fds io);
t_fds	end_update_fds(int pipe_fds[2], t_fds io);
t_fds	in_out(t_data *data, cmd_node *node);

// here_doc
int		handle_heredoc(char *limiter, int fd);

// parsed_utils
t_cmd	*prepare_cmd(t_data *data, cmd_node *node);
t_cmd	*pid_only_cmd(t_malloc *m, pid_t pid);
bool	is_directory(char *path, bool slash);
// pids
void	wait_clean_up(t_fds io, t_data *data);
int		update_exit_code(t_data *data);

// UTILS
// error
void	ft_strerror_q(t_data *data, char *name, char *text, char *err);
void	ft_strerror(t_data *data, char *name, char *text, char *err);

// free
void	ft_free_t_cmd(t_data *data);
void	free_char_array(char **array);

// write
int		safe_write(t_data *data, char *name, char *arg, int fd);

#endif