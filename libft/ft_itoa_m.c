/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_m.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:33:53 by algultse          #+#    #+#             */
/*   Updated: 2024/07/06 20:43:20 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_memory(t_malloc *m, int n, int *len)
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
	return ((char *)ft_malloc(m, sizeof(char) * (*len + 1)));
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

char	*ft_itoa_m(t_malloc *m, int n)
{
	char	*res;
	int		len;

	if (n == -2147483648)
		return (ft_strdup_m(m, "-2147483648"));
	if (n == 0)
		return (ft_strdup_m(m, "0"));
	len = 0;
	res = create_memory(m, n, &len);
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
