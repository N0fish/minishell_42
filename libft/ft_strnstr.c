/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliutykh <aliutykh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:26:16 by algultse          #+#    #+#             */
/*   Updated: 2024/08/13 17:05:16 by aliutykh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!big && !len)
		return (0);
	if (!*little)
		return ((char *)big);
	while (len && *big)
	{
		i = 0;
		while ((*(big + i) == *(little + i)) && *(little + i) && len > i)
		{
			if (!*(little + i + 1))
				return ((char *)big);
			i++;
		}
		big++;
		len--;
	}
	return (NULL);
}

/*
#include <stdio.h>
int	main()
{
	char str1[] = "abcacb";
	char str2[] = "bca";
	
	printf("ft_strnstr: [%s]\n", ft_strnstr(str1, str2, (size_t)9));
	printf("strnstr: [%s]\n", strnstr(str1, str2, (size_t)9));
	return (0);
}
*/