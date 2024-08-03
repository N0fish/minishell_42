/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:36:46 by algultse          #+#    #+#             */
/*   Updated: 2024/01/21 22:01:07 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_printf(unsigned long long nb, char check, int *len)
{
	if (!nb)
		ft_putstr_printf("(nil)", len);
	else
	{
		ft_putstr_printf("0x", len);
		ft_puthex_printf(nb, check, len);
	}
}

void	ft_format(va_list args, const char str, int *len)
{
	if (str == '%')
		ft_putchar_printf('%', len);
	else if (str == 'c')
		ft_putchar_printf(va_arg(args, int), len);
	else if (str == 's')
		ft_putstr_printf(va_arg(args, char *), len);
	else if (str == 'd' || str == 'i')
		ft_putnbr_printf(va_arg(args, int), len);
	else if (str == 'u')
		ft_putuint_printf(va_arg(args, unsigned int), len);
	else if (str == 'x' || str == 'X')
	{
		if (str == 'x')
			ft_puthex_printf(va_arg(args, unsigned int), 'x', len);
		else
			ft_puthex_printf(va_arg(args, unsigned int), 'X', len);
	}
	else if (str == 'p')
		ft_putptr_printf(va_arg(args, unsigned long), 'x', len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len_print;

	if (!str)
		return (-1);
	len_print = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_format(args, *str, &len_print);
		}
		else
			ft_putchar_printf(*str, &len_print);
		str++;
	}
	va_end(args);
	return (len_print);
}
