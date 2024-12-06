#include "../minishell.h"

void handle_sigint(int sig)
{
	(void)sig;
	printf("\n\033[1;35mMinishell~$ \033[0m");
}