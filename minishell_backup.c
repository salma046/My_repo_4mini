#include "minishell.h"

t_minishell	g_minishell;

int execution_main(t_minishell data)
{
    t_node *temp_nodes = data.nodes;
    int pipe_fd[2] = {-1, -1};
    int in_fd = dup(STDIN_FILENO);
    int in_fd2 = dup(STDOUT_FILENO);
    pid_t pid;

	if (temp_nodes->redir)
	{
		ft_check_redirections(temp_nodes);
	}
	if (data.count_pips == 1)
	{
		if (data.nodes->cmd[0] && !strcmp(data.nodes->cmd[0], "exit"))
			ft_exit(&data);
		if (data.nodes->cmd[0] && !strcmp(data.nodes->cmd[0], "cd"))
			ft_cd(&data);
		if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1)
		{
			return (1);
		}
		if (temp_nodes->redir)
		{
			if (temp_nodes->redir->red_type == OUT_REDIR || temp_nodes->redir->red_type == APPEND)
			{
				dup2(temp_nodes->out_file, STDOUT_FILENO);
				close(temp_nodes->out_file);
			}
			if (temp_nodes->redir->red_type == INP_REDIR)
			{
				dup2(temp_nodes->in_file, STDIN_FILENO);
				close(temp_nodes->in_file);
			}
		}
		if (temp_nodes->cmd[0] == NULL)
		{
			dup2(in_fd,0);
			dup2(in_fd2,1);
			close(in_fd);
			close(in_fd2);
			return (data.exit_status);
		}
		if (ft_check_builtins(temp_nodes->cmd[0]) == 1)
		{
			check_command(&data, temp_nodes);
			dup2(in_fd,0);
			dup2(in_fd2,1);
			close(in_fd);
			close(in_fd2);
			return (data.exit_status);
		}
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, handle_sigint);
			signal(SIGQUIT, handle_sigquit);
			char *command_path = find_command_path(temp_nodes->cmd[0], data.envir);
			if (!command_path || execve(command_path, temp_nodes->cmd, data.envirement) == -1)
			{
				fprintf(stderr, "Command '%s' not found\n", temp_nodes->cmd[0]);
				g_minishell.exit_status = 127;
			}
			free_node_list(g_minishell.nodes);
			free_env_list(g_minishell.envir);
			free_env_list(g_minishell.export_env);
			exit(g_minishell.exit_status);
		}
		dup2(in_fd,0);
		dup2(in_fd2,1);
		close(in_fd);
		close(in_fd2);
		if (pid != 0)
			g_minishell.exit_status = 127;
		int	i;
		int	st;
		int	stt;
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
					stt = WEXITSTATUS(st);
			}
			i++;
		}
	}
	else
	{
		while (temp_nodes)
		{
			pipe(pipe_fd);
			pid = fork();
			signal(SIGINT, handle_sigint);
			signal(SIGQUIT, handle_sigquit);
			if (pid == 0) 
			{
				if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1)
					exit(EXIT_FAILURE);
				if (temp_nodes->next_node)
				{
					dup2(pipe_fd[1], STDOUT_FILENO); // Redirect output to pipe.
					close(pipe_fd[1]);
					close(pipe_fd[0]);
					close(in_fd);
				}
				if (temp_nodes->redir && ft_check_redirections(temp_nodes) == 0)
				{
					if (temp_nodes->redir->red_type == OUT_REDIR || temp_nodes->redir->red_type == APPEND)
					{
						dup2(temp_nodes->out_file, STDOUT_FILENO);
						close(temp_nodes->out_file);
					}
					if (temp_nodes->redir->red_type == INP_REDIR)
					{
						dup2(temp_nodes->in_file, STDIN_FILENO);
						close(temp_nodes->in_file);
					}
				}
				if (ft_check_builtins(temp_nodes->cmd[0]) == 1)
				{
					check_command(&data, temp_nodes);
					free_mystructs();
					exit(EXIT_SUCCESS);
				}
				else
				{
					char *command_path = find_command_path(temp_nodes->cmd[0], data.envir);
					if (!command_path)
					{
						fprintf(stderr, "%s: command not found\n", temp_nodes->cmd[0]);
						free(command_path);
						exit(127);
					}
					execve(command_path, temp_nodes->cmd, data.envirement);
					perror("execve");
					exit(127);
				}
			}
			temp_nodes = temp_nodes->next_node;
			dup2(pipe_fd[0],STDIN_FILENO);
			close(pipe_fd[0]); // Close unused read end in the child.
			close(pipe_fd[1]);
		}
		dup2(in_fd,0);
		close(in_fd);
		int	i;
		int	st;
		int	stt;
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
					stt = WEXITSTATUS(st);
			}
			i++;
		}
	}
    return 0;
}

int	main(int ac, char *av[], char **env)
{
	if (ac >= 2)
		return (1);
	(void)av;
	g_minishell.exit_status = 0;
	g_minishell.envirement = env;
	g_minishell.envir = mk_env(g_minishell.envirement);
	g_minishell.export_env = mk_env_4expo(g_minishell.envirement);
	g_minishell.exit_status = 0;

	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		g_minishell.command = readline("Minishell~$ ");
		if (!g_minishell.command)
		{
			printf("exit!\n");
			free_env_list(g_minishell.envir);
			free_env_list(g_minishell.export_env);
			free(g_minishell.command);
			clear_history();
			exit(1);
		}
		if (g_minishell.command[0] == '\0')
			continue;
		add_history(g_minishell.command);	
		g_minishell.tokens = ft_tokenize(g_minishell);
		free(g_minishell.command);
		if (!g_minishell.tokens)
			continue ;
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		g_minishell.nodes = mk_nodes(g_minishell.tokens);
		g_minishell.count_pips = count_pipe(g_minishell.nodes);
		if (main_heredoc(g_minishell.tokens) < 0)
			continue ;
		g_minishell.exit_status = execution_main(g_minishell);
		free_node_list(g_minishell.nodes);
	}
}

