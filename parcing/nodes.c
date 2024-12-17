/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:59:29 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/17 18:37:07 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_redi(enum e_token_type token_t, char *red_file,
		t_redir **redirections, int is_true)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->red_type = token_t;
	new_redir->file = ft_strdup(red_file);
	if (is_true == 1)
		new_redir->is_ambiguous = 1;
	else
		new_redir->is_ambiguous = 0;
	new_redir->next = NULL;
	ft_redi_add_back(redirections, new_redir);
}

void	ft_node_add_back(t_node **node_list, t_node *new_node, int i)
{
	t_node	*arrs;

	arrs = *node_list;
	new_node->cmd[i] = NULL;
	new_node->next_node = NULL;
	if (!node_list || !new_node)
		return ;
	if (*node_list == NULL)
	{
		*node_list = new_node;
		return ;
	}
	while (arrs->next_node != NULL)
		arrs = arrs->next_node;
	arrs->next_node = new_node;
	new_node->prev_node = arrs;
}

void	fill_node(t_token *temp_tokens, t_node **node_list)
{
	t_node	*node;
	t_redir	*redir;
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = temp_tokens;
	redir = NULL;
	node = allocate_for_node(temp_tokens);
	while (tokens && tokens->data_type != PIPE)
	{
		if (tokens->data_type != PIPE && tokens->data_type != WORD)
		{
			fill_redi(tokens->data_type, tokens->next_token->data,
				&redir, tokens->is_ambiguous);
			tokens = tokens->next_token;
		}
		else
			node->cmd[i++] = ft_strdup(tokens->data);
		tokens = tokens->next_token;
	}
	node->redir = redir;
	node->in_file = 0;
	node->out_file = 1;
	ft_node_add_back(node_list, node, i);
}

t_node	*mk_nodes(t_token *tokens)
{
	t_node	*nodes;

	nodes = NULL;
	while (tokens)
	{
		fill_node(tokens, &nodes);
		while (tokens && tokens->data_type != PIPE)
			tokens = tokens->next_token;
		if (tokens && tokens->data_type == PIPE)
			tokens = tokens->next_token;
	}
	g_minishell.count_pips = count_pipe(g_minishell.nodes);
	return (nodes);
}
