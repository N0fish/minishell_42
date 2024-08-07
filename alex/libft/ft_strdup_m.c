/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:43:46 by algultse          #+#    #+#             */
/*   Updated: 2024/06/17 16:02:03 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_m(t_malloc *m, const char *s1)
{
	char	*dst;
	size_t	len;

	len = 0;
	while (s1[len])
		len++;
	dst = (char *)ft_malloc(m, sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		dst[len] = s1[len];
		len++;
	}
	dst[len] = '\0';
	return (dst);
}
