#include "../minishell.h"

void	ft_print(t_node *node)
{
	int	i;

	i = 0;
	while (node->cmd[i])
	{
		write(1, node->cmd[i], ft_strlen(node->cmd[i]));
		if (node->cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

static int	is_all_n(const char *str)
{
	int	i;

	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_n_flag(char **cmd, int *flag, int *start)
{
	*flag = 0;
	*start = 1;
	while (cmd[*start] && strncmp(cmd[*start], "-n", 2) == 0)
	{
		if (is_all_n(cmd[*start]))
		{
			*flag = 1;
			(*start)++;
		}
		else
			break ;
	}
}

void	ft_echo(t_node *node)
{
	int	flag;
	int	start_index;
	int	i;

	flag = 0;
	start_index = 1;
	if (!node->cmd || !node->cmd[1])
	{
		write(1, "\n", 1);
		return ;
	}
	ft_check_n_flag(node->cmd, &flag, &start_index);
	if (!node->cmd[start_index])
		return ;
	i = start_index;
	while (node->cmd[i])
	{
		write(1, node->cmd[i], ft_strlen(node->cmd[i]));
		if (node->cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	g_minishell.exit_status = 0;
}
