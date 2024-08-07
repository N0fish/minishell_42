/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:03:39 by algultse          #+#    #+#             */
/*   Updated: 2023/11/11 18:16:06 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>
int	main()
{
	printf("ft_isalpha: [%d]\n", ft_isalpha('a'));
	printf("isalpha: [%d]\n", isalpha('a'));
	return (0);
}
*/