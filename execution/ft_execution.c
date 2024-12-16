#include "../minishell.h"

int	just_open_files(t_node *node)
{
	if (node->redir->red_type == OUT_REDIR || node->redir->red_type == APPEND)
		close(node->out_file);
	if (node->redir->red_type == INP_REDIR)
		close(node->in_file);
	return (g_minishell.exit_status);
}

void	dup_my_files(t_node *temp_nodes)
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

void	dup2_mystd_files(int in_fd, int in_fd2)
{
	dup2(in_fd, 0);
	dup2(in_fd2, 1);
	close(in_fd);
	close(in_fd2);
}

int	check_my_builtin(t_minishell data, t_node *temp_nodes, int in_fd, int in_fd2)
{
	if (data.nodes->cmd[0] && !strcmp(data.nodes->cmd[0], "exit"))
	{
		ft_exit(temp_nodes);
		return (g_minishell.exit_status);
	}
	if (data.nodes->cmd[0] && !strcmp(data.nodes->cmd[0], "cd"))
	{
		g_minishell.exit_status = ft_cd(&data);
		dup2_mystd_files(in_fd, in_fd2);
		return (g_minishell.exit_status);
	}
	else
	{
		check_command(&data, temp_nodes);
		dup2_mystd_files(in_fd, in_fd2);
		return (g_minishell.exit_status = 1);
	}
}

void	check_my_execute(t_minishell data, t_node *temp_nodes, int in_fd, int in_fd2)
{
	char *command_path;

	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
	if (ft_check_builtins(temp_nodes->cmd[0]) != 1)
	{
		command_path = find_command_path(temp_nodes->cmd[0], data.envir);
		if (!command_path || !ft_strcmp(temp_nodes->cmd[0], ""))
		{
			fprintf(stderr, "%s: command not found\n", temp_nodes->cmd[0]);
			g_minishell.exit_status = 127;
			free_mystructs();
			free(command_path);
			dup2_mystd_files(in_fd, in_fd2);
			exit(g_minishell.exit_status);
		}
		execve(command_path, temp_nodes->cmd, data.envirement);
		free_mystructs();
		perror("execve");
		g_minishell.exit_status = 127;
		exit(g_minishell.exit_status);
	}
}

void	signals_pid(pid_t pid)
{
	int	st;
	int sig;

		waitpid(pid,&st,0);
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

int ft_execute_one_cmd(t_minishell data) 
{
    t_node *temp_nodes;
	int in_fd = dup(STDOUT_FILENO);
	int in_fd2 = dup(STDOUT_FILENO);
	pid_t pid;

	temp_nodes = data.nodes;
	if (data.nodes->cmd[0] == NULL)
		return (just_open_files(temp_nodes));
	else if (temp_nodes->redir)
		dup_my_files(temp_nodes);
	if (ft_check_builtins(temp_nodes->cmd[0]) == 1)
		return (check_my_builtin(data, temp_nodes, in_fd, in_fd2));
	pid = fork();
	if (pid == 0)
		check_my_execute(data, temp_nodes, in_fd, in_fd2);
	dup2_mystd_files(in_fd, in_fd2);
	if (pid != 0)
		g_minishell.exit_status = 127;
	signals_pid(pid);
	return (g_minishell.exit_status);
}

void	part_one(int *pipe_fd, t_node *temp_nodes, int in_fd)
{
	if (temp_nodes->redir && ft_check_redirections(temp_nodes) == -1)
	{
		free_mystructs();
		exit(EXIT_FAILURE);
	}
	if (temp_nodes->next_node)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(in_fd);
	}
}

int	ft_execute_multi_cmd(t_minishell data) 
{
    t_node *temp_nodes;
    int pipe_fd[2] = {-1, -1};
	int in_fd = dup(STDOUT_FILENO);
	pid_t pid;

	temp_nodes = data.nodes;
	while (temp_nodes)
	{
		pipe(pipe_fd);
		pid = fork();
		if (pid == 0) 
		{
			signal(SIGINT, handle_child);
			signal(SIGQUIT, handle_child);
			part_one(pipe_fd, temp_nodes, in_fd);
			if (temp_nodes->redir && ft_check_redirections(temp_nodes) == 0)
				dup_my_files(temp_nodes);
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
					free_mystructs();
					exit(127);
				}
				execve(command_path, temp_nodes->cmd, data.envirement);
				perror("execve");
				free_mystructs();
				exit(127);
			}
		}
		temp_nodes = temp_nodes->next_node;
		dup2(pipe_fd[0],STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (pid);
}
