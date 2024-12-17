/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:49:58 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/17 18:38:01 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	get_env_size(t_env *envir)
{
	int	size;

	size = 0;
	while (envir)
	{
		size++;
		envir = envir->next;
	}
	return (size);
}

static char	*join_env_parts(char *key, char *value)
{
	char	*first_part;
	char	*result;

	first_part = ft_strjoin(key, "=");
	if (!first_part)
		return (NULL);
	result = ft_strjoin(first_part, value);
	free(first_part);
	return (result);
}

char	**mk_tenv_char(t_env *envir)
{
	char	**arr;
	int		i;
	int		size;
	t_env	*tmp;

	i = 0;
	size = get_env_size(envir);
	tmp = envir;
	arr = malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (tmp)
	{
		arr[i] = join_env_parts(tmp->key, tmp->value);
		if (!arr[i])
		{
			free_arr(arr, i);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	arr[i] = (NULL);
	return (arr);
}
