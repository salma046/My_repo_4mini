#include "../minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !(i == 0 && (str[i] == '-'
					|| str[i] == '+')))
			return (0);
		i++;
	}
	return (1);
}

void	error_msg(char *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_mystructs();
	exit(g_minishell.exit_status = 2);
}

void	ft_exit(t_node *tmp_node)
{
	int	i;

	i = 0;
	if (g_minishell.count_pips == 1)
		ft_putstr_fd("exit\n", 2);
	if (!tmp_node->cmd[1])
	{
		free_mystructs();
		exit(g_minishell.exit_status);
	}
	else if (is_numeric(tmp_node->cmd[1]) && !tmp_node->cmd[2])
	{
		g_minishell.exit_status = ft_atoi(tmp_node->cmd[1]) % 256;
		free_mystructs();
		exit(g_minishell.exit_status);
	}
	else if (is_numeric(tmp_node->cmd[1]) && tmp_node->cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_minishell.exit_status = 1;
		return ;
	}
	else
		error_msg(tmp_node->cmd[1]);
}
