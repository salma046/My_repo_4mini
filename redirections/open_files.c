#include "../minishell.h"

int ft_input(char *file_name, t_node *node)
{
    node->in_file = open(file_name, O_RDONLY);
    if (node->in_file == -1)
	{
        g_minishell.exit_status = 1;
		perror("fd");
		return (-1);
	}
    return (0);
}

int ft_output(char *file_name, t_node *node)
{
    node->out_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (node->out_file == -1)
	{
        g_minishell.exit_status = 1;
		perror("fd");
		return (-1);
	}
    return (0);
}

int ft_append(char *file_name, t_node *node)
{
    node->out_file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (node->out_file == -1)
	{
        g_minishell.exit_status = 1;
		perror("fd");
		return (-1);
	}
    return (0);
}
