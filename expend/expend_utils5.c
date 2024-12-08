/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:24:05 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/08 15:46:06 by salaoui          ###   ########.fr       */
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
			t_word = rmp_dollar2(t_word, &i, to_split, to_list, &is_ambiguous);
		else if (t_word[i])
			i++;
	}
	return (t_word);
}

char	*rmp_dollar2(char *t_word, int *i, int to_split, t_token **tokens_list, int **is_ambiguous)
{
	char	*env_var;
	char	*word;

	env_var = NULL;
	env_var = get_env_var(t_word, *i);
	if (env_var != NULL && check_4_space(env_var) == 1 && to_split < 0)
		word = token_edi_env(t_word, env_var, tokens_list);
	else
		word = remplace_doll_str(t_word, env_var);
	if (!word[0])
		**is_ambiguous = 1;
	else
		**is_ambiguous = 0;
	(*i) = 0;
	return (word);
}
