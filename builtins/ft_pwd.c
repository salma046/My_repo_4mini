#include "../minishell.h"

void	ft_pwd(t_node *node)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
	{
		write(node->out_file, pwd, ft_strlen(pwd));
		write(node->out_file, "\n", 1);
	}
	else
		perror("PWDD");
}
