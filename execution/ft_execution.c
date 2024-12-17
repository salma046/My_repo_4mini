#include "../minishell.h"

int	just_open_files(t_node *node)
{
	if (node->is_ambiguous)
		return (g_minishell.exit_status = 1);
	if (node->redir->red_type == OUT_REDIR || node->redir->red_type == APPEND)
		close(node->out_file);
	if (node->redir->red_type == INP_REDIR)
		close(node->in_file);
	return (g_minishell.exit_status);
}

int	check_my_builtin(t_minishell data, t_node *temp_nodes, int in_fd,
		int in_fd2)
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
		g_minishell.exit_status = check_command(&data, temp_nodes);
		dup2_mystd_files(in_fd, in_fd2);
		return (g_minishell.exit_status);
	}
}

void	check_my_execute(t_minishell data, t_node *temp_nodes, int in_fd,
		int in_fd2)
{
	char	*command_path;

	signal(SIGINT, handle_child);
	signal(SIGQUIT, handle_child);
	if (ft_check_builtins(temp_nodes->cmd[0]) != 1)
	{
		command_path = find_command_path(temp_nodes->cmd[0], data.envir);
		if (!command_path)
		{
			fprintf(stderr, "%s: command not found\n", temp_nodes->cmd[0]);
			free_mystructs();
			free(command_path);
			dup2_mystd_files(in_fd, in_fd2);
			exit(g_minishell.exit_status = 127);
		}
		execve(command_path, temp_nodes->cmd, data.envirement);
		free_mystructs();
		perror("execve");
		g_minishell.exit_status = 127;
		exit(g_minishell.exit_status);
	}
}

int	handle_redirection_and_builtins(t_minishell data,
		t_node *temp_nodes, int in_fd, int in_fd2)
{
	if (data.nodes->cmd[0] == NULL)
		return (just_open_files(temp_nodes));
	else if (temp_nodes->redir)
		dup_my_files(temp_nodes);
	if (ft_check_builtins(temp_nodes->cmd[0]) == 1)
		return (check_my_builtin(data, temp_nodes, in_fd, in_fd2));
	if (temp_nodes->is_ambiguous == 1 || !temp_nodes->cmd[0])
	{
		temp_nodes = temp_nodes->next_node;
		dup2_mystd_files(in_fd, in_fd2);
		return (g_minishell.exit_status);
	}
	return (-1);
}

int	ft_execute_one_cmd(t_minishell data)
{
	t_node	*temp_nodes;
	int		in_fd;
	int		in_fd2;
	pid_t	pid;
	int		builtin_status;

	in_fd = dup(STDOUT_FILENO);
	in_fd2 = dup(STDOUT_FILENO);
	temp_nodes = data.nodes;
	builtin_status = handle_redirection_and_builtins(data,
			temp_nodes, in_fd, in_fd2);
	if (builtin_status != -1)
		return (builtin_status);
	pid = fork();
	signal(SIGINT, handle_child);
	if (pid == 0)
		check_my_execute(data, temp_nodes, in_fd, in_fd2);
	dup2_mystd_files(in_fd, in_fd2);
	if (pid != 0)
		g_minishell.exit_status = 127;
	signals_pid(pid);
	return (g_minishell.exit_status);
}
