/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long_long_int_m.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 20:33:53 by algultse          #+#    #+#             */
/*   Updated: 2024/07/21 17:45:43 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_memory(t_malloc *m, long long int n, int *len)
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

static void	write_res(char *res, int len, long long int n)
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

char	*ft_itoa_long_long_int_m(t_malloc *m, long long int n)
{
	char	*res;
	int		len;

	if (n == LLONG_MIN)
		return (ft_strdup_m(m, "-9223372036854775808"));
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
