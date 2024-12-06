#include "../minishell.h"

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
