/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:03:16 by algultse          #+#    #+#             */
/*   Updated: 2024/07/16 14:17:44 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	**malloc_realloc(t_malloc *m)
{
	void	**new_mallocs;
	size_t	i;

	new_mallocs = malloc(sizeof(void *) * (m->len + 1));
	if (new_mallocs == NULL)
		return (NULL);
	i = 0;
	while (i < m->len && m->mallocs)
	{	
		new_mallocs[i] = m->mallocs[i];
		i++;
	}
	if (m->mallocs)
		free(m->mallocs);
	return (new_mallocs);
}

void	ft_free_last(t_malloc *m)
{
	size_t	idx;

	idx = ft_malloc_get_index(m) - 1;
	while (idx > 0)
	{
		if (m->mallocs[idx])
		{
			ft_free(m, m->mallocs[idx]);
			return ;
		}
		idx--;
	}
}

size_t	ft_malloc_get_index(t_malloc *m)
{
	return (m->len - 1);
}

void	ft_malloc_swap_idx(t_malloc *m, size_t c_idx, size_t n_idx)
{
	void	*tmp;

	if (!m || !m->mallocs || c_idx == n_idx \
		|| c_idx == 0 || n_idx == 0 || n_idx >= m->len || c_idx >= m->len)
		return ;
	tmp = m->mallocs[n_idx];
	m->mallocs[n_idx] = m->mallocs[c_idx];
	m->mallocs[c_idx] = tmp;
}

void	ft_malloc_print(t_malloc *m)
{
	size_t	i;

	i = 0;
	while (i < m->len)
	{
		printf("malloc[%zu]: %s\n", i, (char *) m->mallocs[i]);
		i++;
	}	
}
