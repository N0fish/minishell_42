/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:03 by algultse          #+#    #+#             */
/*   Updated: 2024/08/20 13:43:54 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// UTILS
// error
void	ft_strerror_q(t_data *data, char *name, char *text, char *err);
void	ft_strerror(t_data *data, char *name, char *text, char *err);
// free
void	free_cmd(t_data *data, t_cmd *cmd);
// node
bool	is_redirect_node(cmd_node *node);
void	handle_redirect_out(t_data *data, cmd_node **node, int *out_fd);
void	handle_shift_left(t_data *data, cmd_node **node, int *in_fd);
void	handle_redirect_in(t_data *data, cmd_node **node, int *in_fd);
void	handle_shift_right(t_data *data, cmd_node **node, int *out_fd);
// write
int		safe_write(t_data *data, char *name, char *arg, int fd);

#endif