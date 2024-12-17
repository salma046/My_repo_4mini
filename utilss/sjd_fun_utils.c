#include "../minishell.h"

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

t_env	*make_new_expor(char *envir)
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
		cmd_env->value = put_quot2_value(ft_strndup(equal_env + 1,
					ft_strlen(envir + 1)));
		cmd_env->next = NULL;
	}
	return (cmd_env);
}

void	*mk_env_4expo(char **envir)
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
		cmd_env = make_new_expor(envir[i]);
		if (last_node == NULL)
			head = cmd_env;
		else
			last_node->next = cmd_env;
		last_node = cmd_env;
		i++;
	}
	return (head);
}

char	*rm_quot2_value(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		str_len;

	i = 1;
	j = 0;
	str_len = ft_strlen(str);
	if (str_len < 2)
	{
		free(str);
		return (ft_strdup(""));
	}
	result = malloc(sizeof(char) * str_len - 1);
	if (!result)
		return (NULL);
	ft_strncpy(result, str + 1, str_len - 2);
	result[str_len - 2] = '\0';
	free(str);
	return (result);
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
