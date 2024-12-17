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
		return (ft_env(nodes->cmd, data));
	if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(data);
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(nodes);
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(data);
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(nodes);
	if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(nodes);
	if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(data, data->export_env, data->envir));
	return (g_minishell.exit_status);
}

int	check_command(t_minishell *data, t_node *node)
{
	int	pid;

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
			execute_the_builtin(data, node, node->cmd);
			free_mystructs();
			exit(g_minishell.exit_status);
		}
	}
	return (g_minishell.exit_status);
}
