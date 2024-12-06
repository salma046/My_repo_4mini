#include "../minishell.h"

int	is_special_char(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64))
		return (1);
	if ((c >= 91 && c <= 96) || (c >= 123 && c <= 126))
		return (1);
	return (0);
}

int	has_doubled_special_chars(char *token)
{
	int	i;

	if (!token)
		return (0);
	i = 0;
	while (token[i] != '\0' && token[i] != '=')
	{
		if (token[i + 1] != '\0'
			&& is_special_char(token[i])
			&& is_special_char(token[i + 1]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*put_quot2_value(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!result)
		return (NULL);
	result[j++] = '"';
	while (str[i])
		result[j++] = str[i++];
	result[j] = '"';
	result[++j] = '\0';
	free(str);
	return (result);
}

void	key_with_equal(char *data, t_env *envir)
{
	t_env	*head;
	t_env	*new_export;
	char	*split_var;

	head = NULL;
	head = envir;
	while (head && head->next != NULL)
	{
		head = head->next;
	}
	split_var = ft_strchr(data, '=');
	new_export = malloc(sizeof(t_env));
	if (!new_export)
		return ;
	new_export->key = ft_strndup(data, split_var - data);
	new_export->value = put_quot2_value(ft_strdup(split_var + 1));
	new_export->next = NULL;
	if (head == NULL)
		envir = new_export;
	else
		head->next = new_export;
	head = new_export;
}

int	not_valid(char *str)
{
	if (ft_strcmp(str, "=") == 0 || str[0] == '='
		|| ft_isdigit(str[0]) || is_special_char(str[0])
		|| has_doubled_special_chars(str))
		return (1);
	else
		return (0);
}

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

int	search_special_char(char *token_data, t_node *node)
{
	int	i;
	t_node *tmp_node;

	i = 0;
	tmp_node = node;
	while (token_data[i] != '\0' && token_data[i] != '=')
	{
		if (is_special_char(token_data[i]))
		{
			write(tmp_node->out_file, "bash: export: ", ft_strlen("bash: export: "));
			write(tmp_node->out_file, token_data, ft_strlen(token_data));
			write(tmp_node->out_file, "': not a valid identifier", ft_strlen("': not a valid identifier"));
			write(tmp_node->out_file, "\n", 1);
			// printf("bash: export: %s': not a valid identifier\n",
			// 	token_data);// use the write and in the fd;;;;;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_all_tokens(char **args, t_node *nodes)
{
	char	**tmp_args;
	int		i;

	i = 0;
	tmp_args = args;
	while (tmp_args[i])
	{
		if (search_special_char(tmp_args[i], nodes) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	ft_add_to_export_arg(t_node *nodes, t_env *expo_envir,
		t_env *env_envir)
{
	char	**commands;
	char	*token_data;

	commands = nodes->cmd;
	if (!commands || !commands[1] || !expo_envir)
		return ;
	if (check_all_tokens(commands, nodes) == 1)
		return ;
	commands++;
	while (*commands)
	{
		printf("\nthe word will be added is: %s\n", *commands);
		if (*commands == NULL)
		{
			commands++;
			continue ;
		}
		if (not_valid(*commands) == 1)
		{
			write(nodes->out_file, "bash: export: ", ft_strlen("bash: export: "));
			write(nodes->out_file, token_data, ft_strlen(token_data));
			write(nodes->out_file, "': not a valid identifier", ft_strlen("': not a valid identifier"));
			write(nodes->out_file, "\n", 1);
			// printf("bash: export: %s': not a valid identifier\n", token_data);
			return ;
		}
		process_key(*commands, expo_envir, env_envir);
		commands++;
	}
}

void	ft_export(t_minishell *data, t_env *expo_envir, t_env *env_envir)
{
	int	active;
	t_node *tmp_nodes;

	tmp_nodes = data->nodes;
	if (!tmp_nodes->cmd[0] || !expo_envir)
		return ;
	active = 1;
	if ((tmp_nodes->cmd[1] == NULL && tmp_nodes->cmd[0]))
	{
		if (!ft_strcmp(tmp_nodes->cmd[0], "export"))
			ft_env_export_once(tmp_nodes, expo_envir, active);
		// return ;
	}
	else
	{
		active = 0;
		ft_add_to_export_arg(tmp_nodes, expo_envir, env_envir);
	}
	search_check_add_env(expo_envir, env_envir);
}
