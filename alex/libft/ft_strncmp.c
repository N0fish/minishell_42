/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:37:38 by algultse          #+#    #+#             */
/*   Updated: 2023/11/17 16:49:29 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i] && (i + 1) < n)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
#include <stdio.h>
int	main()
{
	char str1[] = "Test strisnt";
	char str2[] = "Test strisns";
	
	printf("ft_strncmp: [%d]\n", ft_strncmp(str1, str2, (size_t)20));
	printf("strncmp: [%d]\n", strncmp(str1, str2, (size_t)20));
	return (0);
}
*/