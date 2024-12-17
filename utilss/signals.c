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
		g_minishell.exit_status = 130;
	}
	if (sig == SIGQUIT)
	{
		g_minishell.exit_status = 131;
	}
}

void	signals_pid(pid_t pid)
{
	int	st;
	int	sig;

	waitpid(pid, &st, 0);
	if (WIFEXITED(st))
		g_minishell.exit_status = WEXITSTATUS(st);
	if (WIFSIGNALED(st))
	{
		sig = WTERMSIG(st);
		if (sig == 2)
		{
			printf("\n");
			g_minishell.exit_status = 130;
		}
		if (sig == 3)
		{
			printf("Quit (core dumped)\n");
			g_minishell.exit_status = 131;
		}
	}
}


static void	exit_child_process(pid_t id, pid_t pid, int st)
{
	int	sig;

	if (id == pid)
	{
		if (WIFEXITED(st))
			g_minishell.exit_status = WEXITSTATUS(st);
		if (WIFSIGNALED(st))
		{
			sig = WTERMSIG(st);
			if (sig == 2)
			{
				printf("\n");
				g_minishell.exit_status = 130;
			}
			if (sig == 3)
			{
				printf("Quit (core dumped)\n");
				g_minishell.exit_status = 131;
			}
		}
	}
}

void	clean_multi_cmd(pid_t pid, t_minishell data)
{
	int		i;
	int		st;
	pid_t	id;

	i = 0;
	while (i < data.count_pips)
	{
		id = waitpid(-1, &st, 0);
		if (id == -1)
			break ;
		exit_child_process(id, pid, st);
		i++;
	}
}
