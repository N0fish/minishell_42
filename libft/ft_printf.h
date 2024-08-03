/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:59:14 by algultse          #+#    #+#             */
/*   Updated: 2023/12/30 16:14:10 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_putchar_printf(char c, int *len);
void	ft_putstr_printf(char *str, int *len);
void	ft_putnbr_printf(int nb, int *len);
void	ft_putuint_printf(unsigned int nb, int *len);
void	ft_puthex_printf(unsigned long long nb, char check, int *len);
void	ft_putptr_printf(unsigned long long nb, char check, int *len);

#endif