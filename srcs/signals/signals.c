#include "minishell.h"

void	handler_sigint(int signal) 
{
	(void)signal;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0); // Не компилирует с ним на mac
	rl_redisplay();
	*g_status = 128 + signal;
}

void	restore_signal(void)
{
	t_sig	action;

	action.sa_handler = SIG_DFL; 
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	ignore_signal(void)
{
	t_sig	action_quit;

	action_quit.sa_handler = SIG_IGN; 
	sigemptyset(&action_quit.sa_mask);
	action_quit.sa_flags = 0;
	// sigaddset(&action.sa_mask, CNTRL_C);
	sigaction(SIGINT, &action_quit, NULL);
	sigaction(SIGQUIT, &action_quit, NULL);
}

void	signals(int *exit_code)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_status = exit_code;
}
