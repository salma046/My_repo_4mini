/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:32:32 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/16 21:52:12 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remp_exit(char *word)
{
	char	*new_word;
	char	*exit_w;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	exit_w = ft_itoa(g_minishell.exit_status);
	new_word = malloc(sizeof(char) * ft_strlen(word) + ft_strlen(exit_w) - 1);
	if (!new_word)
		return (NULL);
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '?')
		{
			while (exit_w[k])
				new_word[j++] = exit_w[k++];
			i += 2;
		}
		else
			new_word[j++] = word[i++];
	}
	new_word[j] = '\0';
	free(word);
	free(exit_w);
	return (new_word);
}

char	*remplace_exit_value(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] == '?')
			return (remp_exit(word));
		i++;
	}
	return (word);
}

char	*rmp_dollar(char *t_word, t_token **to_list, int *is_ambiguous)
{
	int	i;
	int	to_split;

	to_split = -1;
	i = 0;
	while (t_word[i])
	{
		while (t_word[i] == '\'')
			skip_quo(t_word, &i, '\'');
		if (t_word[i] == '"')
			skip_double_quo(t_word, &to_split, &i);
		else if (t_word[i] == '$' && t_word[i + 1] == '$')
		{
			while (t_word[i] == '$' && t_word[i + 1] == '$')
				i += 2;
		}
		else if (t_word[i] == '$' && ft_isalnum(t_word[i + 1]) == 0)
			skip_if_isalnum(t_word, &i);
		else if (t_word[i] == '$')
			t_word = rmp_dollar2(t_word, &i, to_split, to_list, is_ambiguous);
		else if (t_word[i])
			i++;
	}
	return (remplace_exit_value(t_word));
}

char	*rmp_dollar2(char *t_word, int *i, int to_split,
	t_token **tokens_list, int *is_ambiguous)
{
	char	*env_var;
	char	*word;

	env_var = NULL;
	env_var = get_env_var(t_word, *i);
	if (env_var != NULL && check_4_space(env_var) == 1
		 && to_split < 0 && tokens_list)
		word = token_edi_env(t_word, env_var, tokens_list);
	else
		word = remplace_doll_str(t_word, env_var);
	if (!tokens_list)
	{
		return (word);
	}
	if (!word || word[0] == '\0')
	{
		*is_ambiguous = 1;
		g_minishell.is_ambiguous = 1;
	}
	else
		*is_ambiguous = 0;
	(*i) = 0;
	return (word);
}

char	*ft_getenv(char *key, t_env *envir)
{
	t_env	*tmp;

	tmp = envir;
	while (tmp)
	{
		if (!strcmp(key, tmp->key))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
