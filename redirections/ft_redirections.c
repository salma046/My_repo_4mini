#include "../minishell.h"

int	ft_check_redirections(t_node *nodes)
{
	t_node	*tmp_node;
	t_redir	*tmp_redir;

	tmp_node = nodes;
	while (tmp_node)
	{
		tmp_redir = tmp_node->redir;
		while (tmp_redir)
		{
			if (tmp_redir->is_ambiguous == 1)
			{
				fprintf(stderr, "bash: ambiguous redirect\n");
        		g_minishell.exit_status = 1;
				if (g_minishell.count_pips != 1)
					exit (1);
				tmp_node = tmp_node->next_node;
				break;
			}
			if (tmp_redir->red_type == INP_REDIR) //  <
			{
				if (ft_input(tmp_redir->file, tmp_node) < 0)
					return (-1);
			}
			else if (tmp_redir->red_type == OUT_REDIR) // >
			{
				if (ft_output(tmp_redir->file, tmp_node) < 0)
					return (-1);
			}
			else if (tmp_redir->red_type == APPEND) // >>
			{
				if (ft_append(tmp_redir->file, tmp_node) < 0)
					return (-1);
			}
			tmp_redir = tmp_redir->next;
		}
		tmp_node = tmp_node->next_node;
	}

	return (0);
}
