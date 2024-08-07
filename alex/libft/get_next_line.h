/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:42:13 by algultse          #+#    #+#             */
/*   Updated: 2024/04/03 23:17:52 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

# define FREE_STATIC_FD -99

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

char	*get_next_line(int fd);

#endif