/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:28:44 by algultse          #+#    #+#             */
/*   Updated: 2023/11/16 14:37:36 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (size != 0 && count > (size_t)-1 / size)
		return (NULL);
	mem = malloc(size * count);
	if (!mem)
		return (NULL);
	ft_memset(mem, 0, size * count);
	return (mem);
}

/*
#include <stdio.h>
int	main()
{
	char str[] = "0123456789";
	int integer = 0123;	
	
	printf("[%s]\n", str);
	printf("ft_calloc: [%s]\n", (char *)ft_calloc(sizeof(str), sizeof(char)));
	printf("calloc: [%s]\n", (char *)calloc(sizeof(str), sizeof(char)));
	printf("ft_calloc: [%p]\n", ft_calloc(sizeof(integer), sizeof(int)));
	printf("calloc: [%p]\n", calloc(sizeof(integer), sizeof(int)));
	return (0);
}
*/