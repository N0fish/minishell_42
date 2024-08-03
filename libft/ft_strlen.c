/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:51 by algultse          #+#    #+#             */
/*   Updated: 2024/01/21 22:01:20 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

/*
#include <stdio.h>
int	main()
{
	char str[] = "Salut!";
	int	res;

	// res = strlen(str);
	res = ft_strlen(str);
	printf("res: [%d], str: [%s]\n", res, str);
	return (0);
}
*/