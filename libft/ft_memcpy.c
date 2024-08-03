/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:08:34 by algultse          #+#    #+#             */
/*   Updated: 2023/11/17 15:34:33 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char		*p_dest;
	const unsigned char	*p_src;
	size_t				i;

	if (!dest && !src)
		return (0);
	p_dest = (unsigned char *)dest;
	p_src = (const unsigned char *)src;
	i = 0;
	while (i < len)
	{
		p_dest[i] = p_src[i];
		i++;
	}
	return (dest);
}

/*
#include <stdio.h>
int main()
{
	char str[] = "01234";
	char dst[1024];

	ft_memcpy(dst, str, (size_t)4);
	// memcpy(dst, str, (size_t)2);
	printf("dest: [%s]", dst);
	return(0);
}
*/