/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:32:32 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/17 18:45:48 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocat_4_word(char *word, char *exit_w)
{
	char	*new_word;

	new_word = malloc(sizeof(char) * ft_strlen(word) + ft_strlen(exit_w) - 1);
	if (!new_word)
		return (NULL);
	return (new_word);
}

char	*terminate_return(char *new_word, char *word, char *exit_w, int *j)
{
	new_word[*j] = '\0';
	free(word);
	free(exit_w);
	return (new_word);
}

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
	new_word = allocat_4_word(word, exit_w);
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
	return (terminate_return(new_word, word, exit_w, &j));
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

char	*rmp_dollar(char *t_word, t_token **to_list)
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
			t_word = rmp_dollar2(t_word, &i, to_split, to_list);
		else if (t_word[i])
			i++;
	}
	return (remplace_exit_value(t_word));
}
