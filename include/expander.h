/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:45:11 by aliutykh          #+#    #+#             */
/*   Updated: 2024/08/21 15:29:20 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

t_cmd_node		*expander(t_data *data, t_cmd_node *node);
char			*get_dollar_pos(char *str);
int				get_length_var(char *str);
char			*check_vars(t_data *data, char *str);

#endif