/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:36:50 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/05 00:56:16 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dollar_lenth(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] && str[i] != '\'' && is_not_valid_expend(str, i) == 1)
			i++;
		while (str[i] == '\'')
			skip_quo(str, &i, '\'');
		if (str[i] == '"')
			skip_quo(str, &i, '"');
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i + 1] != '$'
			&& is_not_valid_expend(str, i) == 1)
			i++;
		if (str[i] == '$' && str[i + 1] == '$')
		{
			while (str[i + 1] == '$')
				i += 2;
		}
		if (str[i] == '$' && str[i + 1] != '$' && ft_isalnum(str[i + 1]) == 1)
			j = count_lenth2(str, &i);
	}
	return (j);
}

char	*remp_with_null(char *str)
{
	int		i;
	int		j;
	char	*word;

	word = allocate_4_nword(str, NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		fill_word_sgl_quot(word, str, &i, &j);
		if (str[i] != '\'' && str[i] != '"' && str[i] != '$' && str[i
				+ 1] == '$')
			word[j++] = str[i++];
		if (str[i] == '$' && str[i + 1] == '$')
			skip_double_signs(str, &i);
		if (valid_word(str, i) == 1)
			put_env_in_word(str, word, NULL, &i, &j);
	}
	word[j] = '\0';
	return (word);
}

char	*remp_with_value(char *str, char *env_var)
{
	int		i;
	int		j;
	size_t	l;
	char	*word;
	char	*hi;

	word = allocate_4_nword(str, env_var);
	i = 0;
	j = 0;
	while (str[i])
	{
		fill_word_sgl_quot(word, str, &i, &j);
		if (str[i] != '\'' && str[i] != '"' && str[i] != '$' && str[i
				+ 1] == '$')
			word[j++] = str[i++];
		if (str[i] == '$' && str[i + 1] == '$')
			skip_double_signs(str, &i);
		if (valid_word(str, i) == 1)
			l = put_env_in_word(str, word, env_var, &i, &j);
		else if (str[i] && str[i] != '$' && str[i - 1] != '$' && str[i] != '"'
			&& str[i] != '\'')
			i++;
	}
	hi = ft_join_words(word, str, l);
	return (hi);
}

char	*remplace_doll_str(char *data, char *env_var)
{
	char	*word;

	if (env_var == NULL)
		return (remp_with_null(data));
	else
		word = remp_with_value(data, env_var);
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
	return (t_word);
}
