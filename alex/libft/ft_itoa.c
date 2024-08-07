/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 22:09:26 by algultse          #+#    #+#             */
/*   Updated: 2023/11/17 00:14:58 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_memory(int n, int *len)
{
	if (n < 0)
	{
		n = -n;
		(*len)++;
	}
	while (n > 0)
	{
		n /= 10;
		(*len)++;
	}
	return (malloc(sizeof(char) * (*len + 1)));
}

static void	write_res(char *res, int len, int n)
{
	res[len] = '\0';
	len--;
	while (n)
	{
		res[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = 0;
	res = create_memory(n, &len);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		res[0] = '-';
	}
	write_res(res, len, n);
	return (res);
}

/*
#include <stdio.h>
int main()
{
	printf ("ft_itoa: [%s]\n", ft_itoa(12345));
	return (0);
}
*/