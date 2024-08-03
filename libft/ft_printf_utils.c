/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:24:53 by algultse          #+#    #+#             */
/*   Updated: 2023/12/28 20:23:17 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_printf(char c, int *len)
{
	write (1, &c, 1);
	(*len)++;
}

void	ft_putstr_printf(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write (1, &*str, 1);
		str++;
		(*len)++;
	}
}

void	ft_putnbr_printf(int nb, int *len)
{
	if (nb == -2147483648)
	{
		ft_putchar_printf('-', len);
		ft_putchar_printf('2', len);
		nb = 147483648;
	}
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_printf('-', len);
	}
	if (nb < 10)
	{
		ft_putchar_printf(nb + '0', len);
		return ;
	}
	ft_putnbr_printf(nb / 10, len);
	ft_putnbr_printf(nb % 10, len);
}

void	ft_putuint_printf(unsigned int nb, int *len)
{
	if (nb < 10)
	{
		ft_putchar_printf(nb + '0', len);
		return ;
	}
	ft_putuint_printf(nb / 10, len);
	ft_putuint_printf(nb % 10, len);
}

void	ft_puthex_printf(unsigned long long nb, char check, int *len)
{
	if (nb > 15)
	{
		ft_puthex_printf(nb / 16, check, len);
		ft_puthex_printf(nb % 16, check, len);
	}
	if (nb <= 9)
		ft_putchar_printf(nb + '0', len);
	if (nb > 9 && nb < 16 && check == 'x')
		ft_putchar_printf(97 - 10 + nb, len);
	if (nb > 9 && nb < 16 && check == 'X')
		ft_putchar_printf(65 - 10 + nb, len);
}
