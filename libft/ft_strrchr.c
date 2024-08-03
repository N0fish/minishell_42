/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:46:34 by algultse          #+#    #+#             */
/*   Updated: 2023/11/09 14:33:40 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	p = NULL;
	while (*s)
	{
		if (*s == (char)c)
			p = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (p);
}

/*
#include <stdio.h>
int	main()
{
	char str[] = "Test strisnt";
	
	printf("ft_strrchr: [%s]\n", ft_strrchr(str, 's'));
	printf("strrchr: [%s]\n", strrchr(str, 's'));
	return (0);
}
*/