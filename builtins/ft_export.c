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
		if (token[i + 1] != '\0' && is_special_char(token[i])
			&& is_special_char(token[i + 1]))
		{
			return (1);
		}
		i++;
	}
	return (0);
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

int	check_all_tokens(char **args, t_node *nodes)
{
	char	**tmp_args;
	int		i;

	i = 0;
	tmp_args = args;
	while (tmp_args[i])
	{
		if (search_special_char(tmp_args[i], nodes) == 1)
			return (g_minishell.exit_status = 127);
		i++;
	}
	return (0);
}

int	ft_export(t_minishell *data, t_env *expo_envir, t_env *env_envir)
{
	int		active;
	t_node	*tmp_nodes;

	tmp_nodes = data->nodes;
	if (!tmp_nodes->cmd[0] || !expo_envir)
		return (0);
	active = 1;
	if (check_all_tokens(tmp_nodes->cmd, tmp_nodes) != 0)
		return (g_minishell.exit_status = 127);
	if ((tmp_nodes->cmd[1] == NULL && tmp_nodes->cmd[0]))
	{
		if (!ft_strcmp(tmp_nodes->cmd[0], "export"))
			g_minishell.exit_status = ft_env_export_once(tmp_nodes, expo_envir,
					active);
	}
	else
	{
		active = 0;
		g_minishell.exit_status = ft_add_to_export_arg(tmp_nodes, expo_envir,
				env_envir);
	}
	search_check_add_env(expo_envir, env_envir);
	return (g_minishell.exit_status);
}
