/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:01:14 by algultse          #+#    #+#             */
/*   Updated: 2023/11/11 18:15:14 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main()
{
	printf("ft_isalnum: [%d]\n", ft_isalnum('\n'));
	printf("isalnum: [%d]\n", isalnum('\n'));
	return (0);
}
*/