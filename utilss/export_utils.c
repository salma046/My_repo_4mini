#include "../minishell.h"

t_env	*make_new_node(char *envir)
{
	t_env	*cmd_env;
	char	*equal_env;

	cmd_env = (t_env *)malloc(sizeof(t_env));
	if (!cmd_env)
		exit(1);
	equal_env = ft_strchr(envir, '=');
	if (equal_env != NULL)
	{
		cmd_env->key = ft_strndup(envir, equal_env - envir);
		cmd_env->value = ft_strndup(equal_env + 1, ft_strlen(envir + 1));
		cmd_env->next = NULL;
	}
	return (cmd_env);
}

t_env	*mk_env(char **envir)
{
	int		i;
	t_env	*head;
	t_env	*last_node;
	t_env	*cmd_env;

	i = 0;
	head = NULL;
	last_node = NULL;
	while (envir[i] != NULL)
	{
		cmd_env = make_new_node(envir[i]);
		if (last_node == NULL)
			head = cmd_env;
		else
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	return (head);
}

char	**mk_tenv_char(t_env *envir)
{
	t_env	*tmp;
	char	**arr;
	int		i;
	int		size;
	char	*first_part;
	char	*second_part;

	size = 0;
	tmp = envir;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	tmp = envir;
	i = 0;
	while (tmp)
	{
		first_part = ft_strjoin(tmp->key, "=");
		if (!first_part)
		{
			free(arr);
			return (NULL);
		}
		second_part = ft_strjoin(first_part, tmp->value);
		free(first_part);
		if (!second_part)
		{
			free(arr);
			return (NULL);
		}
		arr[i++] = second_part;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	add_struc_2_env(t_env *expo_env, t_env *envir)
{
	t_env	*head;
	t_env	*new_env;

	head = envir;
	while (head && head->next != NULL)
	{
		head = head->next;
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = ft_strdup(expo_env->key);
	new_env->value = rm_quot2_value(ft_strdup(expo_env->value));
	new_env->next = NULL;
	if (head == NULL)
		envir = new_env;
	else
		head->next = new_env;
	head = new_env;
}

void	search_check_add_env(t_env *expo_envir, t_env *env_envir)
{
	t_env	*to_check;

	to_check = expo_envir;
	while (to_check)
	{
		if (to_check->value == NULL)
		{
			to_check = to_check->next;
			continue ;
		}
		else if (check_key(to_check->key, env_envir) != 1)
		{
			add_struc_2_env(to_check, env_envir);
		}
		to_check = to_check->next;
	}
}
