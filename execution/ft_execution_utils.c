#include "../minishell.h"

void	dup_my_files(t_node *temp_nodes)
{
	if (temp_nodes->redir->red_type == OUT_REDIR
		|| temp_nodes->redir->red_type == APPEND)
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

void	part_one(int *pipe_fd, t_node *temp_nodes, int in_fd, int red_result)
{
	if (temp_nodes->redir && red_result == -1)
	{
		free_mystructs();
		exit(EXIT_FAILURE);
	}
	if (temp_nodes->is_ambiguous == 1 || !temp_nodes->cmd[0])
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

int	ft_execute_multi_cmd(t_minishell data, int red_result)
{
	t_node	*temp_nodes;
	int		pipe_fd[2];
	int		in_fd;
	pid_t	pid;
	char	*cmd_path;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	in_fd = dup(STDOUT_FILENO);
	temp_nodes = data.nodes;
	while (temp_nodes)
	{
		pipe(pipe_fd);
		pid = fork();
		signal(SIGINT, handle_child);
		signal(SIGQUIT, handle_child);
		if (pid == 0)
		{
			part_one(pipe_fd, temp_nodes, in_fd, red_result);
			if (temp_nodes->redir)
				dup_my_files(temp_nodes);
			if (ft_check_builtins(temp_nodes->cmd[0]) == 1)
			{
				check_command(&data, temp_nodes);
				free_mystructs();
				exit(g_minishell.exit_status);
				printf("minishell exit status is: %d\n",
					g_minishell.exit_status);
			}
			else
			{
				cmd_path = find_command_path(temp_nodes->cmd[0], data.envir);
				if (!cmd_path)
				{
					fprintf(stderr, "%s: command not found\n",
						temp_nodes->cmd[0]);
					free(cmd_path);
					free_mystructs();
					exit(g_minishell.exit_status = 127);
				}
				execve(cmd_path, temp_nodes->cmd, data.envirement);
				perror("execve");
				free_mystructs();
				exit(127);
			}
		}
		temp_nodes = temp_nodes->next_node;
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	return (pid);
}
