/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:54:38 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/13 22:42:59 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*allocate_4_nword(char *str, char *env_var)
{
	int		word_lenth;
	int		i;
	char	*word;

	word_lenth = count_dollar_lenth(str);
	i = ft_strlen(str);
	if (env_var == NULL)
		word = malloc(sizeof(char) * i - word_lenth + 1);
	else
		word = malloc(sizeof(char) * i - word_lenth + ft_strlen(env_var) + 1);
	if (!word)
		return (NULL);
	return (word);
}

void	fill_word_double_quot(char *word, char *str, int *i, int *j)
{
	int	t;

	t = 0;
	word[(*j)++] = str[(*i)++];
	while (str[*i] && str[*i] != '"' && t != 1)
	{
		if (str[*i] == '$' && str[(*i) + 1] == '$')
		{
			while (str[*i] == '$' && str[(*i) + 1] == '$')
				(*i) += 2;
		}
		if (str[*i] != '$')
			word[(*j)++] = str[(*i)++];
		else
			t = 1;
	}
	if (str[*i] == '"')
		word[(*j)++] = str[(*i)++];
}

void	fill_word_sgl_quot(char *word, char *str, int *i, int *j)
{
	while (str[*i] == '\'')
	{
		word[(*j)++] = str[(*i)++];
		while (str[*i] && str[*i] != '\'')
			word[(*j)++] = str[(*i)++];
		if (str[*i] == '\'')
			word[(*j)++] = str[(*i)++];
	}
	if (str[*i] == '"')
		fill_word_double_quot(word, str, i, j);
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[(*i) + 1] != '$'
		&& is_not_valid_expend(str, *i) == 1)
		word[(*j)++] = str[(*i)++];
}

int	valid_word(char *str, int i)
{
	if (str[i] && str[i] == '$' && str[i + 1] != '$' && ft_isalnum(str[i
				+ 1]) == 1)
		return (1);
	else
		return (0);
}

void	skip_double_signs(char *str, int *i)
{
	while (str[*i] == '$' && str[(*i) + 1] == '$')
		(*i) += 2;
}
