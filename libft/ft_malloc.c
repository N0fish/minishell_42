/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:03:10 by algultse          #+#    #+#             */
/*   Updated: 2024/08/16 14:41:07 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_free_array(t_malloc *m, void **array)
{
	size_t	it;

	it = 0;
	if (!m || !array)
		return ;
	while (array[it])
	{
		ft_free(m, array[it]);
		it++;
	}
	ft_free(m, array);
}

void	ft_free(t_malloc *m, void *block)
{
	size_t	idx;

	if (m == NULL || m->mallocs == NULL || !block)
		return ;
	idx = 0;
	while (idx < m->len && m->mallocs[idx] != block)
		idx++;
	if (!m->mallocs[idx] || m->mallocs[idx] != block)
		return ;
	free(m->mallocs[idx]);
	m->mallocs[idx] = NULL;
	while (idx < m->len - 1)
	{
		m->mallocs[idx] = m->mallocs[idx + 1];
		idx++;
	}
	m->mallocs[idx] = NULL;
	m->len--;
}

void	ft_free_all(t_malloc *m)
{
	if (m == NULL)
		return ;
	if (m->mallocs == NULL)
	{
		free(m);
		return ;
	}
	while (m->len > 0)
	{
		m->len--;
		if (m->mallocs[m->len])
		{
			free(m->mallocs[m->len]);
			m->mallocs[m->len] = NULL;
		}
	}
	free(m->mallocs);
	m->mallocs = NULL;
	free(m);
}

void	*ft_malloc(t_malloc *m, int blocks)
{
	void	*new_block;

	if (!m)
		m = init_malloc();
	if (m == NULL || blocks <= 0)
		return (NULL);
	new_block = malloc(blocks);
	if (new_block == NULL)
	{
		ft_free_all(m);
		exit(1);
	}
	m->mallocs = malloc_realloc(m);
	if (m->mallocs == NULL)
	{
		free(new_block);
		new_block = NULL;
		ft_free_all(m);
		exit(1);
	}
	m->mallocs[m->len] = new_block;
	m->len++;
	return (new_block);
}

t_malloc	*init_malloc(void)
{
	t_malloc	*m;

	m = (t_malloc *)malloc(sizeof(t_malloc));
	if (m == NULL)
		exit(1);
	m->mallocs = NULL;
	m->len = 0;
	return (m);
}
