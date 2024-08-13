/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:06:24 by alex              #+#    #+#             */
/*   Updated: 2024/08/13 13:49:43 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "libft.h"

enum TokenType{
	CHAR_PIPE		= '|',
	CHAR_GREATER	= '>',
	CHAR_LESSER		= '<',
	CHAR_QUOTE		= '\"',

	CHAR_NULL 		= 0,
	CHAR_GENERAL	= -1,
	TOKEN			= -1,
};

# define TOKEN_DELIM "\" \t\n\r\a"

typedef struct s_token {
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

t_token		*lexer(char *line);
void		print_tokens(t_token *token);

#endif