/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:11 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/09 11:44:02 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_minishell	g_minishell;

int	count_lenth2(char *str, int *i)
{
	int	j;

	j = 0;
	(*i)++;
	j++;
	while (check_is_num(str, *i) == 1)
	{
		(*i)++;
		j++;
	}
	while (str[*i])
		(*i)++;
	return (j);
}

void	skip_2quo(char *tokens_word, int *i, int quot)
{
	(*i)++;
	while (tokens_word[*i] && tokens_word[*i] != quot && tokens_word[*i] != '$')
		(*i)++;
	if (tokens_word[*i] == quot)
		(*i)++;
}

void	skip_quo(char *tokens_word, int *i, int quot)
{
	(*i)++;
	while (tokens_word[*i] && tokens_word[*i] != quot)
		(*i)++;
	if (tokens_word[*i] == quot)
		(*i)++;
}

void	skip_double_quo(char *tokens_word, int *to_split, int *i)
{
	int	t;

	t = 0;
	(*i)++;
	(*to_split) = -1;
	while (tokens_word[*i] && tokens_word[*i] != '"' && t != 1)
	{
		if (tokens_word[*i] == '$' && tokens_word[*i + 1] == '$')
		{
			while (tokens_word[*i] == '$' && tokens_word[*i + 1] == '$')
				(*i) += 2;
		}
		if (tokens_word[*i] != '$')
			(*i)++;
		else
		{
			(*to_split) = 1;
			t = 1;
		}
	}
	t = 0;
	if (tokens_word[*i] == '"')
		(*i)++;
}

void	skip_if_isalnum(char *tokens_word, int *i)
{
	if (tokens_word[*i] == '$')
		(*i)++;
	while (tokens_word[*i] && tokens_word[*i] != '"' && tokens_word[*i] != '\''
		&& tokens_word[*i] != '$')
		(*i)++;
}

int	count_env(t_env *envir)
{
	int		count;
	t_env	*tmp;

	tmp = envir;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

char	*ft_getenv(char *key, t_env *envir)
{
	t_env *tmp;

	tmp = envir;
	while(tmp)
	{
		if (!strcmp(key, tmp->key))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_var(char *str, int i)
{
	char	*env_var;
	char	*env_value;
	int		j;
	int		temp;

	i++;
	temp = 0;
	j = i;
	while (str[i] == '$')
		i++;
	while (check_is_num(str, i) == 1)
		i++;
	env_var = (char *)malloc(i - j + 1);
	if (!env_var)
		return (NULL);
	while (j < i)
		env_var[temp++] = str[j++];
	env_var[temp] = '\0';
	env_value = ft_getenv(env_var, g_minishell.envir);
	free(env_var);
	if (env_value)
		return (env_value);
	else
		return (NULL);
}
