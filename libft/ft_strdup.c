/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:08 by algultse          #+#    #+#             */
/*   Updated: 2023/11/09 15:25:05 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	len;

	len = 0;
	while (s1[len])
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		dst[len] = s1[len];
		len++;
	}
	dst[len] = '\0';
	return (dst);
}

/*
#include <stdio.h>
int	main()
{
	char *crs = "01234";
	char *duplicate;

	// duplicate = strdup(crs);
	duplicate = ft_strdup(crs);
	printf("crs: [%s]\n", crs);
	printf("strdup(duplicate): [%s]\n", duplicate);
	free(duplicate);
	return (0);
}
*/