/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:03 by algultse          #+#    #+#             */
/*   Updated: 2024/08/08 16:43:42 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

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

#endif