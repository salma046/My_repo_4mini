/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:02:13 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/17 09:14:52 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ret_syntax_err(t_minishell g_minishell)
{
	printf("syntax error\n");
	g_minishell.exit_status = 2;
	g_minishell.tokens = NULL;
	return (g_minishell.tokens);
}

t_token	*parsing(t_minishell g_minishell)
{
	t_token	*tokens;

	tokens = g_minishell.tokens;
	if (tokens->data_type == 1)
		return (ret_syntax_err(g_minishell));
	while (tokens)
	{
		if (tokens->next_token == NULL && tokens->data_type != 0)
			return (ret_syntax_err(g_minishell));
		if ((tokens->data_type == 2 || tokens->data_type == 3
				|| tokens->data_type == 4 || tokens->data_type == 5)
			&& tokens->next_token->data_type != 0)
			return (ret_syntax_err(g_minishell));
		if (tokens->data_type == 1)
		{
			if (tokens->next_token != NULL
				&& tokens->next_token->data_type == 1)
				return (ret_syntax_err(g_minishell));
		}
		tokens = tokens->next_token;
	}
	return (g_minishell.tokens);
}
