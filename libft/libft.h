/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:12:11 by algultse          #+#    #+#             */
/*   Updated: 2024/08/09 23:45:10 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include "get_next_line.h"
# include "ft_printf.h"
# include "ft_malloc.h"

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
void			*ft_memset(void *str, int value, size_t len);
void			ft_bzero(void *str, size_t len);
void			*ft_memcpy(void *dest, const void *src, size_t len);
void			*ft_memmove(void *dest, const void *src, size_t len);
size_t			ft_strlcpy(char *dest, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t len);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_itoa_m(t_malloc *m, int n);
char			*ft_itoa_long_long_int_m(t_malloc *m, long long int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_ternary(int cond, int then, int or);
long			ft_atoi_long(const char *str);
long long int	ft_atoi_long_long_int(const char *str);
char			*ft_strjoin_m(t_malloc *m, char const *s1, char const *s2);
char			**ft_split_m(t_malloc *m, char const *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup_m(t_malloc *m, const char *s1);
char			*ft_substr_m(t_malloc *m, char const *s, \
							unsigned int start, size_t len);
size_t			ft_array_len(char **arg);
char			**ft_strtok(char *str, char *charset);
char			*ft_strcpy(char *dst, const char *src);
void			ft_free_char_array(char **array);

#endif