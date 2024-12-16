#include "../minishell.h"

int	ft_check_redirections(t_node *nodes)
{
	t_node	*tmp_node;
	t_redir	*tmp_redir;

	tmp_node = nodes;
	char *str = "bash: ambiguous redirect\n";
	while (tmp_node)
	{
		tmp_redir = tmp_node->redir;
		while (tmp_redir)
		{
			printf("the file is nameeed: %s \n", tmp_redir->file);
			if (tmp_redir->is_ambiguous == 1)
			{
				write(2, str, ft_strlen(str));
				g_minishell.exit_status = 1;
				if (g_minishell.count_pips == 1 || !tmp_node->next_node)
					return (-1);
				else
					tmp_node = tmp_node->next_node;
				continue;
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
