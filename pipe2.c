#include "minishell.h"

void	free_node_pipe(t_node *node)
{
	if (!node)
		return ;
	free(node->cmd);
	free(node);
}

void	free_node_list_pipe(t_node *head)
{
	t_node	*temp;

	while (head)
	{
		temp = head;
		head = head->next_node;
		free_node_pipe(temp);
	}
}

char	*find_command_path_pipe(char *command, char **env)
{
	char	*path_env;
	char	full_path[1024];
	int		i = 0, j = 0, k;

	printf("\033[0;31mcommand:%s\033[0m\n", command);
	path_env = NULL;
	i = 0, j = 0, k = 0;
	while (env[i] != NULL)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			path_env = env[i] + 5;
		}
		i++;
	}
	if (!path_env)
	{
		errno = ENOENT;
		perror("PATH not found");
		return (NULL);
	}
	i = 0;
	while (path_env[i] != '\0')
	{
		ft_memset(full_path, 0, sizeof(full_path));
		k = 0;
		while (path_env[i] != ':' && path_env[i] != '\0')
		{
			full_path[k++] = path_env[i++];
		}
		full_path[k++] = '/';
		j = 0;
		while (command[j] != '\0')
		{
			full_path[k++] = command[j++];
		}
		full_path[k] = '\0';
		if (access(full_path, X_OK) == 0)
		{
			return (ft_strdup(full_path));
		}
		if (path_env[i] == ':')
			i++;
	}
	errno = ENOENT;
	return (NULL);
}

int	execute_piped_commands(t_node *nodes, char **env)
{
	int		pipefd[2];
	int		prev_pipe;
	pid_t	pid;
	char	*command_path;

	prev_pipe = -1;
	int status; // hadi hta lmen be3d w xofi xhal radi treturna f l exit
	while (nodes)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == -1)
		{
			perror("Fork");
			return (-1);
		}
		printf("ths pid:%d\n\n", pid);
		if (pid == 0)
		{
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (nodes->next_node)
			{
				printf("nexxt-->%s", nodes->next_node->cmd[1]);
				dup2(pipefd[1], STDOUT_FILENO);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			command_path = find_command_path_pipe(nodes->cmd[0], env);
			if (!command_path)
			{
				printf("%s: command not found\n", nodes->cmd[0]);
				exit(127);
			}
			execve(command_path, nodes->cmd, env);
			perror("execve");
			exit(1);
		}
		else
		{
			printf("fd:%d", pipefd[1]);
			close(pipefd[1]);
			if (prev_pipe != -1)
			{
				close(prev_pipe);
			}
			prev_pipe = pipefd[0];
		}
		nodes = nodes->next_node;
	}
	free_node_list_pipe(nodes);
	while (wait(&status) > 0)
		;
	return (0);
}
