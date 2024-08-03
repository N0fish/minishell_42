/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:08:42 by algultse          #+#    #+#             */
/*   Updated: 2023/11/15 22:54:18 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*d_dest;
	const unsigned char	*s_src;

	d_dest = (unsigned char *)dest;
	s_src = (const unsigned char *)src;
	if (d_dest == s_src)
		return (dest);
	if (d_dest > s_src && d_dest < s_src + len)
	{
		d_dest += len;
		s_src += len;
		while (len--)
			*(--d_dest) = *(--s_src);
	}
	else
	{
		while (len--)
			*d_dest++ = *s_src++;
	}
	return (dest);
}

/*
#include <stdio.h>
int main()
{
	char str[10] = "0123456789";
	
	ft_memmove(str + 3, str + 4, (size_t)3);
	// memmove(&str[3], &str[4], (size_t)3);
	printf("str new: [%s]", str);
	return (0);
}
*/