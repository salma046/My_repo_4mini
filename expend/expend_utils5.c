/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:24:05 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/16 16:28:36 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_new_edi_word(char *word, enum e_token_type token_t,
		t_token **tokens_list, int i)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->data = word;
	new_token->data_type = token_t;
	new_token->next_token = NULL;
	new_token->is_ambiguous = i;
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

