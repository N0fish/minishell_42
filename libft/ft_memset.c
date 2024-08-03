/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:22 by algultse          #+#    #+#             */
/*   Updated: 2023/11/09 15:23:27 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int value, size_t len)
{
	size_t			i;
	unsigned char	*buf;

	i = 0;
	buf = (unsigned char *)str;
	while (i < len)
	{
		buf[i] = (unsigned char)value;
		i++;
	}
	return (str);
}

/*
#include <stdio.h>
int main() {
    char str[6] = "ABCDE";
    ft_memset(str, 87, 2);
    // memset(str, 87, 2);
    printf("%s\n", str);
    return 0;
}
*/