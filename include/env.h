#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_envp {
	char			*key;
	char			*value;
	bool			display;
	struct s_envp	*prev;
	struct s_envp	*next;
}				t_envp;

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