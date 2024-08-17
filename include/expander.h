/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:45:11 by alex              #+#    #+#             */
/*   Updated: 2024/08/17 11:33:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "parser.h"
# include "executor.h"

cmd_node	    *expander(t_data *data, cmd_node *node);

char            *get_dollar_pos(char *str);
int		        get_length_var(char *str);
char		    *check_vars(t_data *data, char *str);

#endif