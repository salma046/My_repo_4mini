#include "../minishell.h"

void	print_ambig_msg(void)
{
	char	*str;

	str = "bash: ambiguous redirect\n";
	write(2, str, ft_strlen(str));
}

int	process_redir(t_redir *tmp_redir, t_node *tmp_node)
{
	if (tmp_redir->file[0] == '\0' || tmp_redir->is_ambiguous == 1)
	{
		print_ambig_msg();
		tmp_node->is_ambiguous = 1;
		g_minishell.exit_status = 1;
		return (-1);
	}
	if (tmp_redir->red_type == INP_REDIR)
	{
		if (ft_input(tmp_redir->file, tmp_node) < 0)
			return (-1);
	}
	if (tmp_redir->red_type == OUT_REDIR)
	{
		if (ft_output(tmp_redir->file, tmp_node) < 0)
			return (-1);
	}
	if (tmp_redir->red_type == APPEND)
	{
		if (ft_append(tmp_redir->file, tmp_node) < 0)
			return (-1);
	}
	return (0);
}

int	handle_redirection(t_node *tmp_node)
{
	t_redir	*temp_redir;

	temp_redir = tmp_node->redir;
	while (temp_redir)
	{
		if (process_redir(temp_redir, tmp_node) < 0)
			return (-1);
		temp_redir = temp_redir->next;
	}
	return (0);
}

int	ft_check_redirections(t_node *nodes)
{
	t_node	*tmp_node;

	tmp_node = nodes;
	while (tmp_node)
	{
		if (handle_redirection(tmp_node) < 0)
		{
			tmp_node = tmp_node->next_node;
			continue ;
		}
		tmp_node = tmp_node->next_node;
	}
	return (0);
}
