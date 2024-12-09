#include "../minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_minishell.exit_status = 130;
}

//sigquit == 131 exit status
