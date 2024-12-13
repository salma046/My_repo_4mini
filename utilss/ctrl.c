#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_minishell.exit_status = 130;
}
void	handle_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_minishell.exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		g_minishell.exit_status = 131;
	}
}
// void	handle_here_sigquit(int sig)
// {
// 	(void)sig;
// 	printf("sigquit in child\n");
// 	g_minishell.exit_status = 0;
// 	exit(g_minishell.exit_status);
// }


void	handle_quit(int sig)
{
	(void)sig;
}

//sigquit == 131 exit status
