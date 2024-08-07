/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:17:25 by algultse          #+#    #+#             */
/*   Updated: 2023/11/11 17:55:56 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main()
{
	printf("ft_isprint: [%d]\n", ft_isprint(31));
	printf("isprint: [%d]\n", isprint(31));
	return (0);
}
*/