/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:24:05 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/05 00:39:49 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_new_edi_word(char *word, enum e_token_type token_t,
		t_token **tokens_list)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->data = word;
	new_token->data_type = token_t;
	new_token->next_token = NULL;
	ft_lstadd_back_token(tokens_list, new_token);
}

char	*fill_middle_part(char *env_var, int *i)
{
	char	*middle_part;
	char	modified_part[256];
	int		j;

	j = 0;
	while (env_var[*i] == ' ' || env_var[*i] == '\t' || env_var[*i] == '\n')
		(*i)++;
	while (env_var[*i] != ' ' && env_var[*i] != '\t' && env_var[*i] != '\n'
		&& env_var[*i] != '\0')
	{
		modified_part[j] = env_var[*i];
		j++;
		(*i)++;
	}
	modified_part[j] = '\0';
	middle_part = strdup(modified_part);
	return (middle_part);
}

char	*fill_first_part(char *env_var, int *i)
{
	char	modified_part[256];
	char	*result;
	int		j;

	j = 0;
	while (env_var[*i] != ' ' && env_var[*i] != '\t' && env_var[*i] != '\n'
		&& env_var[*i] != '\0')
	{
		modified_part[j] = env_var[*i];
		j++;
		(*i)++;
	}
	modified_part[j] = '\0';
	result = strdup(modified_part);
	return (result);
}

char	*rmp_dollar2(char *t_word, int *i, int to_split, t_token **tokens_list)
{
	char	*env_var;
	char	*word;

	env_var = NULL;
	env_var = get_env_var(t_word, *i);
	if (env_var != NULL && check_4_space(env_var) == 1 && to_split < 0)
		word = token_edi_env(t_word, env_var, tokens_list);
	else
		word = remplace_doll_str(t_word, env_var);
	(*i) = 0;
	return (word);
}
