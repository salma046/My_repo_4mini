#include "../minishell.h"

int	is_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	handle_error(int flag, char *cmd)
{
	if (flag == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	if (flag == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
	}
	if (flag == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
	return (0);
}

char	*is_valid_cmd(char *cmd)
{
	struct stat	state;

	if (is_slash(cmd) && access(cmd, F_OK) != 0 && !handle_error(1, cmd))
		exit(g_minishell.exit_status = 127);
	if (is_slash(cmd) && access(cmd, F_OK) == 0 && !stat(cmd, &state))
	{
		if (S_ISREG(state.st_mode) && access(cmd, X_OK) != 0 && !handle_error(2,
				cmd))
			exit(g_minishell.exit_status = 126);
		if (S_ISREG(state.st_mode) && access(cmd, X_OK) == 0)
			return (cmd);
		if (S_ISDIR(state.st_mode) && !handle_error(3, cmd))
			exit(g_minishell.exit_status = 126);
	}
	return (NULL);
}

char	*find_command_in_path(char *command, char *path_env, int k)
{
	char	full_path[1024];
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (path_env[i] != '\0')
	{
		ft_memset(full_path, 0, sizeof(full_path));
		k = 0;
		while (path_env[i] != ':' && path_env[i] != '\0')
			full_path[k++] = path_env[i++];
		full_path[k++] = '/';
		j = 0;
		while (command[j] != '\0')
			full_path[k++] = command[j++];
		full_path[k] = '\0';
		if (access(full_path, X_OK) == 0)
			return (ft_strdup(full_path));
		if (path_env[i] == ':')
			i++;
	}
	errno = ENOENT;
	return (NULL);
}

char	*find_command_path(char *command, t_env *env)
{
	char	*path_env;
	int		i;

	path_env = NULL;
	i = 0;
	path_env = ft_getenv("PATH", env);
	if (!command || command[0] == '\0')
		return (NULL);
	if (is_valid_cmd(command))
		return (command);
	if (!path_env)
	{
		errno = ENOENT;
		perror("PATH not found");
		return (NULL);
	}
	return (find_command_in_path(command, path_env, 0));
}
