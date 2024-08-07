/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:25:36 by algultse          #+#    #+#             */
/*   Updated: 2024/07/10 15:18:33 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**do_res_malloc_m(t_malloc *m, char const *s, char c, size_t *pnts)
{
	int			sep;
	const char	*p_s;

	if (!s)
		return (NULL);
	p_s = s;
	*pnts = 0;
	sep = -1;
	while (*p_s)
	{
		if ((!sep || sep == -1) && *p_s == c)
			sep = 1;
		else if ((sep || sep == -1) && *p_s != c)
		{
			sep = 0;
			(*pnts)++;
		}
		p_s++;
	}
	return ((char **)ft_malloc(m, sizeof(char *) * (*pnts + 1)));
}

static char	*get_str_chunk_m(t_malloc *m, char const *s, char c, size_t *i)
{
	char		*res;
	size_t		n;

	if (!s)
		return (NULL);
	while (s[*i] == c)
		(*i)++;
	n = 0;
	while (s[*i + n] != c && s[*i + n])
		n++;
	if (!n)
		return (NULL);
	res = (char *)ft_malloc(m, sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	n = 0;
	while (s[*i] != c && s[*i])
	{
		res[n++] = s[*i];
		(*i)++;
	}
	res[n] = '\0';
	return (res);
}

static void	free_all_m(t_malloc *m, char **res)
{
	size_t	i;

	if (!m || !res)
		return ;
	i = 0;
	while (res[i])
	{
		ft_free(m, res[i]);
		i++;
	}
}

char	**ft_split_m(t_malloc *m, char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	n;
	size_t	pnts;

	res = do_res_malloc_m(m, s, c, &pnts);
	if (!res)
		return (NULL);
	i = 0;
	n = 0;
	while (n < pnts)
	{
		res[n] = get_str_chunk_m(m, s, c, &i);
		if (!res[n])
		{
			free_all_m(m, res);
			return (NULL);
		}
		n++;
	}
	res[n] = NULL;
	return (res);
}

/*
#include <stdio.h>
int main()
{
	char **res = ft_split("Salut    Hello    Privet", ' ');
	while (*res)
		printf ("ft_split: [%s]\n", *res++);
	return (0);
}
*/