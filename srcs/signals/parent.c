/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:25 by algultse          #+#    #+#             */
/*   Updated: 2024/07/29 11:59:04 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(int *exit_code)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_status = exit_code;
}

void	handler_sigint(int signal) 
{
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	*g_status = 128 + signal;
}

void	parent_handler(int signal)
{
	*g_status = 128 + signal;
	if (signal == SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	if (signal == SIGINT)
		ft_putstr_fd("\n", 2);
}

void	parent_signals(void)
{
	signal(SIGQUIT, parent_handler);
	signal(SIGINT, parent_handler);
}
