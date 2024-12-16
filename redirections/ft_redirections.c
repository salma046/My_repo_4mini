#include "../minishell.h"


int	process_redir(t_redir *tmp_redir, t_node *tmp_node)
{
	char	*str;

	str = "bash: ambiguous redirect\n";
	if (g_minishell.is_ambiguous == 1)
	{
		write(2, str, ft_strlen(str));
		g_minishell.is_ambiguous = 0;
		g_minishell.exit_status = 1;
		return (-1);
	}
	if (tmp_redir->red_type == INP_REDIR)
	{
		if (ft_input(tmp_redir->file, tmp_node) < 0)
			return (-1);
	}
	else if (tmp_redir->red_type == OUT_REDIR)
	{
		if (ft_output(tmp_redir->file, tmp_node) < 0)
			return (-1);
	}
	else if (tmp_redir->red_type == APPEND)
	{
		if (ft_append(tmp_redir->file, tmp_node) < 0)
			return (-1);
	}
	return (0);
}

int	handle_redirections(t_node *node)
{
	t_redir	*temp_redir;

	temp_redir = node->redir;
	while (temp_redir)
	{
		if (process_redir(temp_redir, node) < 0)
			return (-1);
		temp_redir = temp_redir->next;
	}
	return (0);
}


int	ft_check_redirections(t_node *nodes)
{
	t_node *tmp_nodes;

	tmp_nodes = nodes;
	while (tmp_nodes)
	{
		if (handle_redirections(tmp_nodes) < 0)
		{
			tmp_nodes = tmp_nodes->next_node;
			continue;
		}
		tmp_nodes = tmp_nodes->next_node;
	}
	return (0);
}




// int	ft_check_redirections(t_node *nodes)
// {
// 	t_node	*tmp_node;
// 	t_redir	*tmp_redir;

// 	tmp_node = nodes;
// 	char *str = "bash: ambiguous redirect\n";
// 	while (tmp_node)
// 	{
// 		tmp_redir = tmp_node->redir;
// 		while (tmp_redir)
// 		{
// 			if (g_minishell.is_ambiguous == 1)
// 			{
// 				write(2, str, ft_strlen(str));
// 				g_minishell.exit_status = 1;
// 				g_minishell.is_ambiguous = 0;
// 				tmp_node = tmp_node->next_node;
// 				continue;
// 			}
// 			if (tmp_redir->red_type == INP_REDIR) //  <
// 			{
// 				if (ft_input(tmp_redir->file, tmp_node) < 0)
// 					return (-1);
// 			}
// 			else if (tmp_redir->red_type == OUT_REDIR) // >
// 			{
// 				if (ft_output(tmp_redir->file, tmp_node) < 0)
// 					return (-1);
// 			}
// 			else if (tmp_redir->red_type == APPEND) // >>
// 			{
// 				if (ft_append(tmp_redir->file, tmp_node) < 0)
// 					return (-1);
// 			}
// 			tmp_redir = tmp_redir->next;
// 		}
// 		tmp_node = tmp_node->next_node;
// 	}

// 	return (0);
// }
