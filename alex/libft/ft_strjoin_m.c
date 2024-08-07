/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_m.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:00:52 by algultse          #+#    #+#             */
/*   Updated: 2024/06/17 16:06:12 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_m(t_malloc *m, char const *s1, char const *s2)
{
	char	*s_dest;
	char	*p_dest;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s_dest = (char *)ft_malloc(m, sizeof(char) * (len + 1));
	if (!s_dest)
		return (NULL);
	p_dest = s_dest;
	while (*s1)
		*s_dest++ = *s1++;
	while (*s2)
		*s_dest++ = *s2++;
	*s_dest = '\0';
	return (p_dest);
}

/*
#include <stdio.h>
int main()
{
	printf ("ft_strjoin: [%s]\n", ft_strjoin("Hello", "Hi"));
	return (0);
}
*/