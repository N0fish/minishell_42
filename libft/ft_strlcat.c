/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:43:41 by algultse          #+#    #+#             */
/*   Updated: 2023/11/17 11:54:20 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	s_dst;
	size_t	s_src;
	size_t	i;

	s_dst = 0;
	s_src = 0;
	while (src[s_src])
		s_src++;
	if (!dstsize)
		return (s_src);
	while (dst[s_dst] && s_dst < dstsize)
		s_dst++;
	i = 0;
	while (s_dst + i < dstsize - 1 && src[i])
	{
		dst[s_dst + i] = src[i];
		i++;
	}
	if (s_dst < dstsize)
		dst[s_dst + i] = '\0';
	return (s_dst + s_src);
}

/*
#include <stdio.h>
int	main()
{
	char src[] = "Test string";
	char dst[15] = "0123456789";
	char dst2[15] = "0123456789";

	printf("sizeof вернула: %zu\n", strlen(dst));
	printf("ft_strlcat вернула: %zu %zu\n", \
		ft_strlcat(dst, src, sizeof(dst)), sizeof(dst));
	printf("sizeof вернула: %zu\n", strlen(dst2));
	printf("strlcat вернула: %zu\n", strlcat(dst2, src, sizeof(dst2)));
	printf("dst ft_strlcat теперь содержит: '%s'\n", dst);
	printf("dst strlcat теперь содержит: '%s'\n", dst2);
	return (0);
}
*/