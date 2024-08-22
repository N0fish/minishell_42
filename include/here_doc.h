/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:00:03 by algultse          #+#    #+#             */
/*   Updated: 2024/08/22 19:37:34 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "data.h"

// here_doc
int		handle_heredoc(t_data *data, char *limiter);
char	*process_key(t_data *data, char *line, int len_key[2], int *diff);
// is_there_env
char	*seek_key_in_str(t_data *data, char *str, int *res);
char	*is_there_env(t_data *data, char *line);
char	*replace_key_to_value(char *str, int *res, const char *value);
char	*seek_key_in_str(t_data *data, char *str, int *res);
char	*seek_env_or_exit_code(t_data *data, char *key);

#endif