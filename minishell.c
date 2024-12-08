#include "minishell.h"

t_minishell	g_minishell;

int execution_main(t_minishell data)
{
    t_node *temp_nodes = data.nodes;
    int pipe_fd[2] = {-1, -1};
    int in_fd = dup(STDIN_FILENO);
    pid_t pid;

	if (data.count_pips == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1)
				exit(EXIT_FAILURE);
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
				exit(EXIT_SUCCESS);
			}
			else
			{
				char *command_path = find_command_path(temp_nodes->cmd[0], data.envirement);
				if (!command_path)
				{
					fprintf(stderr, "%s: command not found\n", temp_nodes->cmd[0]);
					exit(127);
				}
				execve(command_path, temp_nodes->cmd, data.envirement);
				free(command_path);
				perror("execve");
				g_minishell.exit_status = 127;
				exit(g_minishell.exit_status);
			}
		}
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
					exit(EXIT_SUCCESS);
				}
				else
				{
					char *command_path = find_command_path(temp_nodes->cmd[0], data.envirement);
					if (!command_path)
					{
						fprintf(stderr, "%s: command not found\n", temp_nodes->cmd[0]);
						exit(127);
					}
					execve(command_path, temp_nodes->cmd, data.envirement);
					free(command_path);
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

void fre_the_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next_token;
		free(current->data);
		free(current);
		current = next;
	}
}

// void	export_the_status()

int	main(int ac, char *av[], char **env)
{
	signal(SIGINT, handle_sigint);
	if (ac >= 2)
		return (1);
	(void)av;
	g_minishell.exit_status = 0;
	g_minishell.envirement = env;
	g_minishell.envir = mk_env(g_minishell.envirement);
	g_minishell.export_env = mk_env_4expo(g_minishell.envirement);
	// export_the_status();

	while (1)
	{
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
		add_history(g_minishell.command);	
		g_minishell.tokens = ft_tokenize(g_minishell);
		free(g_minishell.command);
		if (!g_minishell.tokens)
			continue ;
		g_minishell.tokens = rm_qotes(g_minishell.tokens);
		g_minishell.tokens = parsing(g_minishell);
		if (main_heredoc(g_minishell.tokens) < 0)
			continue ;
		g_minishell.nodes = mk_nodes(g_minishell.tokens);
		g_minishell.count_pips = count_pipe(g_minishell.nodes);
		execution_main(g_minishell);
		// fre_the_tokens(g_minishell.tokens);
		free_node_list(g_minishell.nodes);
	}
}
