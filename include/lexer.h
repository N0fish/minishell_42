/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:06:24 by alex              #+#    #+#             */
/*   Updated: 2024/08/17 14:26:14 by alex             ###   ########.fr       */
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
	HEREDOC_IN		= '>'+13,
	HEREDOC_OUT		= '<'+13,
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

void		lexer_quotes(char ch, t_token **token, int *j, int *state);
void		lexer_redirections(char *input, t_token **token, int i, int *j);
void		lexer_general(char *input, t_token **token, int i, int *j);
void		lexer_other_state(char ch, t_token **token, int *j, int *state);
void		lexer_heredoc(char *input, t_token **token, int *i, int *j);

int			char_type(char ch);
int			is_heredoc(char *input, int i);
void		token_data_init(t_token* token, int size);
void		strip_quotes(char *src, char *dest);
void		lexer_destroy(t_token **token);

#endif