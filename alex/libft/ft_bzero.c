/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:46:04 by algultse          #+#    #+#             */
/*   Updated: 2023/11/06 16:58:02 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t len)
{
	unsigned char	*buf;

	buf = (unsigned char *)str;
	while (len--)
		buf[len] = 0;
}

/*
#include <stdio.h>
int	main()
{
	char str[] = "Salut!";

	// bzero(str, (size_t)3);
	ft_bzero(str, (size_t)2);
	printf("str: [%s]\n", str);
	return (0);
}
*/