/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:15:25 by algultse          #+#    #+#             */
/*   Updated: 2024/07/29 11:59:04 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int signal)
{
	*g_status = 128 + signal;
	exit(*g_status);
}

void	child_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
