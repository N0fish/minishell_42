/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:06:24 by alex              #+#    #+#             */
/*   Updated: 2024/08/16 17:55:31 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include "libft.h"
# include "executor.h"

enum TokenType{
	CHAR_PIPE		= '|',
	CHAR_GREATER	= '>',
	CHAR_LESSER		= '<',
	CHAR_QOUTE		= '\'',
	CHAR_DQOUTE		= '\"',
	CHAR_WHITESPACE	= ' ',

	CHAR_NULL 		= 0,
	CHAR_GENERAL	= -1,
	TOKEN_QUOTE		= -2,
	TOKEN_DQUOTE	= -3,
	TOKEN			= -1,
};

enum {
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	
	STATE_IN_ESCAPESEQ,
	STATE_GENERAL,
};

# define TOKEN_DELIM " \t\n\r\a"

typedef struct s_token {
	struct s_malloc	*m;
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

t_token		*lexer(t_data *data, char *line);
t_token		*lexer_build(t_data *data, char *line, int state);
void		print_tokens(t_token *token);

t_token		*token_init(t_malloc *m, t_token *token, int size);
t_token		*check_lexer(t_data *data, t_token *token, int state);

int			char_type(char ch);
void		token_data_init(t_token* token, int size);
void		strip_quotes(char *src, char *dest);
void		lexer_destroy(t_token **token);

#endif