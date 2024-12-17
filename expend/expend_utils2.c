/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:46:11 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/17 18:48:38 by salaoui          ###   ########.fr       */
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
