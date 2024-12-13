#include "../minishell.h"

int	ft_check_builtins(char *command)
{
	if (!command || command[0] == '\0')
		return (-1);
	if (!ft_strcmp(command, "echo"))
		return (1);
	if (!ft_strcmp(command, "cd"))
		return (1);
	if (!ft_strcmp(command, "pwd"))
		return (1);
	if (!ft_strcmp(command, "exit"))
		return (1);
	if (!ft_strcmp(command, "export"))
		return (1);
	if (!ft_strcmp(command, "unset"))
		return (1);
	if (!ft_strcmp(command, "env"))
		return (1);
	return (0);
}
int	execute_the_builtin(t_minishell *data, t_node *nodes, char **cmd)
{
	if (!ft_strcmp(cmd[0], "env"))
	{
		printf("This is builtin: env\n");
		ft_env(nodes->cmd, data);
	}
	if (!ft_strcmp(cmd[0] , "unset"))
	{
		printf("This is builtin: unset\n");
		ft_unset(data);
	}
	if (!ft_strcmp(cmd[0], "echo"))
	{
		printf("This is builtin: echo\n");
		ft_echo(nodes);
	}
	if (!ft_strcmp(cmd[0], "cd"))
	{
		printf("This is builtin: cd\n");
		ft_cd(data);
	}
	if (!ft_strcmp(cmd[0], "pwd"))
	{
		printf("This is builtin: pwd\n");
		ft_pwd(nodes);
	}
	if (!ft_strcmp(cmd[0], "exit"))
	{
		printf("This is builtin: export\n");
		ft_exit(data);
	}
	if (!ft_strcmp(cmd[0], "export"))
	{
		printf("This is builtin: export\n");
		return (ft_export(data, data->export_env, data->envir));
	}
	return (0);
}

int	check_command(t_minishell *data, t_node *node)
{
	int	pid;

	// printf("hi from builtins!!\n");

	if (data->count_pips == 1)
	{
		return (execute_the_builtin(data, node, node->cmd));
	}
	else if (data->count_pips > 1)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork");
			return (-1);
		}
		else if (pid == 0)
		{
			// sigint
			// sigquit
			execute_the_builtin(data, node, node->cmd);
			free_mystructs();
			exit(0); //Child proccess;;; // save the return exit status to be put on the $?
		}
	}
	return (0);
	// and then in the end save the exit staus here 
	// execute_the_builtin; // Already done
}
