/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 10:05:58 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/17 11:29:16 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node_list(t_node *node_list)
{
	t_node	*current;
	t_node	*next;

	current = node_list;
	if (!node_list)
		return ;
	while (current != NULL)
	{
		next = current->next_node;
		free_node(current);
		current = next;
	}
	g_minishell.nodes = NULL;
}

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free_env_node(head);
		head = tmp;
	}
	head = NULL;
}

void	free_mystructs(void)
{
	fre_the_tokens(g_minishell.tokens);
	free_env_list(g_minishell.envir);
	free_env_list(g_minishell.export_env);
	free_node_list(g_minishell.nodes);
}

void	fre_the_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	if (!tokens)
		return ;
	while (current)
	{
		next = current->next_token;
		if (current->data)
			free(current->data);
		free(current);
		current = next;
	}
	g_minishell.tokens = NULL;
}
