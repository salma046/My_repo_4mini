#include "../minishell.h"

void	ft_env(char **cmds, t_minishell *data)
{
	t_env	*tmp;

	// node = data->nodes;
	tmp = data->envir;
	// printf ("[%s]\n", node->cmd[0]);
	// printf ("[%s]\n", node->cmd[1]);
	if (tmp && cmds[1] == NULL)
	{
		while (tmp)
		{
			if (tmp->value != NULL)
			{
				printf("%s", tmp->key);
				printf("%c", '=');
				printf("%s\n", tmp->value);
			}
			tmp = tmp->next;
		}
	}
	else
		fprintf (stderr, "env: %s: No such file or directory\n", cmds[1]);
}
