#include "../minishell.h"

// I called the function normaly of env.
void	ft_env(t_node *node, t_minishell **data)
{
	t_env	*tmp;

	tmp = (*data)->envir;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			write(node->out_file, tmp->key, ft_strlen(tmp->key));
			write(node->out_file, "=", 1);
			write(node->out_file, tmp->value, ft_strlen(tmp->value));
			write(node->out_file, "\n", 1);
			// printf("%s", tmp->key);
			// printf("%c", '=');
			// printf("%s\n", tmp->value);
		}
		tmp = tmp->next;
	}
}
