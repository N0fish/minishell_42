/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:23:10 by algultse          #+#    #+#             */
/*   Updated: 2023/11/11 18:26:23 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main()
{
	printf("ft_tolower: [%c]\n", ft_tolower('Z'));
	printf("tolower: [%c]\n", tolower('Z'));
	return (0);
}
*/