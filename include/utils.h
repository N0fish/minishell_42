/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:03 by algultse          #+#    #+#             */
/*   Updated: 2024/08/21 15:21:04 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// UTILS
// error
void	ft_strerror_q(t_data *data, char *name, char *text, char *err);
void	ft_strerror(t_data *data, char *name, char *text, char *err);
void	handle_access_errors(t_data *data, t_cmd *cmd);
int		update_exit_code(t_data *data);
void	display_error(t_data *data, char *lim);
// free
void	free_cmd(t_data *data, t_cmd *cmd);
// string
bool	ft_isempty(const char *str);
bool	is_not_special_char(char c, char c_1);
// node
bool	is_redirect_node(t_cmd_node *node);
int		handle_redirect_out(t_data *data, t_cmd_node **node, int *out_fd);
int		handle_shift_left(t_data *data, t_cmd_node **node, int *in_fd);
int		handle_redirect_in(t_data *data, t_cmd_node **node, int *in_fd);
int		handle_shift_right(t_data *data, t_cmd_node **node, int *out_fd);
// write
int		safe_write(t_data *data, char *name, char *arg, int fd);

#endif