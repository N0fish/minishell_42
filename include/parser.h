/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:06:24 by aliutykh          #+#    #+#             */
/*   Updated: 2024/08/21 15:27:09 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_node_type
{
	NODE_PIPE			= 1,
	NODE_REDIRECT_OUT	= 2,
	NODE_REDIRECT_IN	= 3,
	NODE_HEREDOC_OUT	= 4,
	NODE_HEREDOC_IN		= 5,
	NODE_CMDPATH		= 6,
	NODE_Q_CMDPATH		= 7,
	NODE_DQ_CMDPATH		= 8,
	NODE_ARGUMENT		= 9,
	NODE_Q_ARGUMENT		= 10,
	NODE_DQ_ARGUMENT	= 11,
	NODE_DATA			= 12,
	NODE_ERROR			= -1,
}			t_node_type;

typedef struct s_cmd_node
{
	char				*data;
	int					type;
	struct s_cmd_node	*left;
	struct s_cmd_node	*right;
}				t_cmd_node;

t_cmd_node	*check_parser(t_cmd_node **node);

void		cmd_set(t_cmd_node *node, char *data, t_node_type type, \
					t_cmd_node *next);
void		cmd_attach(t_cmd_node *root, t_cmd_node *left, t_cmd_node *right);
void		cmd_set_type(t_cmd_node *node, t_node_type nodetype);
void		cmd_set_data(t_cmd_node *node, char *data);
bool		check_tokentype(int tok_type, t_token **token, char **bufferptr);
bool		only_check_tokentype(int tok_type, t_token **token, \
					char **bufferptr);
void		show_cmd_tree(t_cmd_node *node);
//
t_cmd_node	*cmd_delete(t_cmd_node *node);
t_cmd_node	*cmd_delete_error(t_cmd_node *node);
t_cmd_node	*set_null(t_token **token);
t_cmd_node	*cmd_define(t_cmd_node *root, t_node_type type, t_cmd_node *left, \
					t_cmd_node *right);
//
t_cmd_node	*cmd_argument(t_token **token);
t_cmd_node	*cmd_simple(t_token **token);
t_cmd_node	*cmd(t_token **token);
t_cmd_node	*heredoc(t_token **token);
t_cmd_node	*redirect(t_token **token);
t_cmd_node	*parser(t_data *data, t_token **token);
t_cmd_node	*heredoc_or_redirecit(t_token **token);

#endif