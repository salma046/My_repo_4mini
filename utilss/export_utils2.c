#include "../minishell.h"

void	process_key(char *data, t_env *expo_envir, t_env *env_envir)
{
	char	*split_var;
	char	*key;

	split_var = ft_strchr(data, '=');
	if (!split_var)
		key_without_equal(data, expo_envir);
	else
	{
		key = ft_strndup(data, split_var - data);
		if (check_key(key, expo_envir))
		{
			remove_node(&expo_envir, key);
			remove_node(&env_envir, key);
		}
		free(key);
		key_with_equal(data, expo_envir);
	}
}

void	error_export(char *str)
{
	write(STDERR_FILENO, "bash: export: ", ft_strlen("bash: export: "));
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "': not a valid identifier",
		ft_strlen("': not a valid identifier"));
	write(STDERR_FILENO, "\n", 1);
}

int	search_special_char(char *token_data, t_node *node)
{
	int		i;
	t_node	*tmp_node;

	i = 0;
	tmp_node = node;
	while (token_data[i] != '\0' && token_data[i] != '=')
	{
		if (is_special_char(token_data[i]))
		{
			error_export(token_data);
			return (1);
		}
		i++;
	}
	return (0);
}

int	not_valid(char *str)
{
	if (ft_strcmp(str, "=") == 0 || str[0] == '=' || ft_isdigit(str[0])
		|| is_special_char(str[0]) || has_doubled_special_chars(str))
		return (1);
	else
		return (0);
}

int	ft_add_to_export_arg(t_node *nodes, t_env *expo_envir, t_env *env_envir)
{
	char	**commands;

	commands = nodes->cmd;
	if (!commands || !commands[1] || !expo_envir)
		return (-1);
	commands++;
	while (*commands)
	{
		if (*commands == NULL)
		{
			commands++;
			continue ;
		}
		if (not_valid(*commands) == 1)
		{
			error_export(*commands);
			return (0);
		}
		process_key(*commands, expo_envir, env_envir);
		commands++;
	}
	return (0);
}
