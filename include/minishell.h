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
# include "executor.h"
# include "libft.h"
# include "ft_malloc.h"
# include "macros.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"

extern int	*g_status;
typedef struct sigaction	t_sig;

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
}				t_cmd;


// BUILTINS
// builtin_utils
bool	ft_isstralnum(char *str);
bool	ft_match_any(t_data *data, char *str, char *any);
char	**transform_envp(t_malloc *m, t_envp *envp);
void	modif_display(t_envp *envp, char *key, bool display);
// builtins
t_data	*init_builtins(char **argv, char **envp);
bool	use_builtin(t_data *data, cmd_node *node, t_fds fds, bool exit_display);
bool	fork_builtin(t_data *data, cmd_node *cmd, t_fds fds);
// cd_builtin
int		cd_builtin(t_data *data, cmd_node *cmd);
// echo_builtin
int		echo_builtin(t_data *data, cmd_node *arg);
// env_builtin
int		env_builtin(t_data *data);
// exit_builtin
void	exit_builtin(t_data *data, cmd_node *arg, bool display);
// export_builtin_utils
int		declare_env_builtin(t_data *data);
// export_builtin
int		export_builtin(t_data *data, cmd_node *arg);
// pwd_builtin
char	*getcwd_builtin(t_data *data);
int		pwd_builtin(t_data *data);
// unset_builtin
int		unset_builtin(t_data *data, cmd_node *arg);

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

// EXEC
// command
char	**get_command_args(t_data *data, cmd_node *node);
// exec
int		exec_entry(t_data *data, cmd_node *node);
// fds_utils
bool	fds_ok(t_fds fds);
int		find_final_fd(t_data *data, cmd_node **red, \
						int node_type, int open_modes[2]);
void	close_fds(t_fds fds);
// fds
t_fds	init_fds(t_fds io);
t_fds	update_fds(t_fds fds, t_fds io);
t_fds	end_update_fds(t_fds fds, t_fds io);
t_fds	in_out(t_data *data, cmd_node *node);
// here_doc
int		handle_heredoc(t_data *data, char *limiter);
// parsed_utils
bool	is_directory(char *path, bool slash);
t_cmd	*prepare_cmd(t_data *data, cmd_node *node);
bool	try_dir_or_file(char *path);
// pids
int		update_exit_code(t_data *data);
pid_t	exec_child(t_data *data, t_fds fds, t_cmd *cmd, char **envp);

// SIGNALS
void	ignore_signal(void);
void	restore_signal(void);
void	signals(int *exit_code);

// UTILS
// error
void	ft_strerror_q(t_data *data, char *name, char *text, char *err);
void	ft_strerror(t_data *data, char *name, char *text, char *err);
// free
void	free_cmd(t_data *data, t_cmd *cmd);
// node
bool	is_redirect_node(cmd_node *node);
// write
int		safe_write(t_data *data, char *name, char *arg, int fd);

#endif