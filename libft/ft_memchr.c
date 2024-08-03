/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:08:15 by algultse          #+#    #+#             */
/*   Updated: 2023/11/07 11:08:18 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	const unsigned char	*str;

	str = (const unsigned char *)s;
	while (len--)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main()
{
	const char str[10]= "0123456789";
	char	c = '9';
	const char *found = (const char *)ft_memchr(str, c, strlen(str));

	// printf("str [%s]\n", str);
	if (found) {
        printf("Character '%c' found at position %ld.\n", c, found - str);
    } else {
        printf("Character '%c' not found.\n", c);
    }
    return (0);
}
*/