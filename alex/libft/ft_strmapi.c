/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:10:33 by algultse          #+#    #+#             */
/*   Updated: 2023/11/14 15:29:49 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (!s || !f)
		return (0);
	str = (malloc(sizeof(*s) * (ft_strlen(s) + 1)));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
#include <stdio.h>

char my_func(unsigned int i, char str)
{
	printf("My inner function: index = [%d] and [%c]\n", i, str);
	return str - 32;
}

int main()
{
	printf("The result is 1 [%s]\n\n", "salut");
	printf("\nThe result is ft_strmapi [%s]\n", ft_strmapi("salut", my_func));
	return (0);
}
*/