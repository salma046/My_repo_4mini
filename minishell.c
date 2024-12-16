#include "minishell.h"

t_minishell	g_minishell;

int execution_main(t_minishell data)
{
    t_node *temp_nodes = data.nodes;
    // int pipe_fd[2] = {-1, -1};
    int in_fd = dup(STDOUT_FILENO);
    // int in_fd2 = dup(STDOUT_FILENO);
    pid_t pid;

	if (temp_nodes->redir && ft_check_redirections(temp_nodes) )
		return (-1);
	if (data.count_pips == 1)
	{
		ft_execute_one_cmd(data);
	}
	else
	{
		pid = ft_execute_multi_cmd(data);
		dup2(in_fd,0);
		close(in_fd);
		int	i;
		int	st;
		int sig;
		pid_t	id;
		i = 0;
		while(i < data.count_pips)
		{
			id = waitpid(-1,&st,0);
			if(id == -1)
				break ;
			if(id == pid)
			{
				if(WIFEXITED(st))
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
			i++;
		}
	}
    return 0;
}

void	init_data(char **env)
{
	g_minishell.exit_status = 0;
	g_minishell.envirement = env;
	g_minishell.envir = mk_env(g_minishell.envirement);
	g_minishell.export_env = mk_env_4expo(g_minishell.envirement);
	g_minishell.exit_status = 0;
}

void	parent_signals()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	free_structs(int i)
{
	if (i == 1)
	{
		printf("exit!\n");
		free_env_list(g_minishell.envir);
		free_env_list(g_minishell.export_env);
		free(g_minishell.command);
		clear_history();
		exit(0);
	}
	else if (i == 2)
	{
		fre_the_tokens(g_minishell.tokens);
		free_node_list(g_minishell.nodes);
		free(g_minishell.command);
	}
}

int	main(int ac, char *av[], char **env)
{
	if (ac >= 2)
		return (1);
	(void)av;
	init_data(env);
	while (1)
	{
		parent_signals();
		g_minishell.command = readline("Minishell~$ ");
		if (!g_minishell.command)
			free_structs(1);
		if (g_minishell.command[0] == '\0')
			continue;
		add_history(g_minishell.command);
		g_minishell.tokens = ft_tokenize(g_minishell);
		if (!g_minishell.tokens)
			continue ;
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		if (!g_minishell.tokens || main_heredoc(g_minishell.tokens) < 0)
			continue ;
		g_minishell.nodes = mk_nodes(g_minishell.tokens);
		g_minishell.count_pips = count_pipe(g_minishell.nodes);
		execution_main(g_minishell);
		free_structs(2);
	}
}

