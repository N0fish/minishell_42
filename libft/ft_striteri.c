/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:16:11 by algultse          #+#    #+#             */
/*   Updated: 2023/11/14 15:45:15 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/*
#include <stdio.h>
void my_func(unsigned int i, char *str)
{
	printf("My inner function: index = [%d] nd the string is [%s]\n", i, str);
}

int main()
{
	char	str[] = "salut";
	printf("The result is 1 [%s]\n\n", str);
	ft_striteri(str, my_func);
	printf("\nThe result is ft_striteri [%s]\n", str);
	return (0);
}
*/