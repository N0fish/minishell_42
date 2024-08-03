/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:14:46 by algultse          #+#    #+#             */
/*   Updated: 2023/11/17 16:49:36 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*(src + i))
		i++;
	if (!dstsize)
		return (i);
	while (--dstsize && *src)
		*dest++ = *src++;
	*dest = '\0';
	return (i);
}

/*
#include <stdio.h>
int	main()
{
	char src[] = "Test string";
	char dst[10];

	size_t result = ft_strlcpy(dst, src, sizeof(dst));
	// size_t result = strlcpy(dst, src, sizeof(dst));
	printf("strlcpy вернула: %zu\n", result);
	printf("dst теперь содержит: '%s'\n", dst);
	return (0);
}
*/