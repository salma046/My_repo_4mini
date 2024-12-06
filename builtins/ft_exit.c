#include "../minishell.h"

void	ft_exit(t_minishell *data)
{
	t_token	*tmp_tokens;
	int		exit_status;

	tmp_tokens = data->tokens;
	exit_status = 0;
	if (tmp_tokens->next_token)
	{
		exit_status = ft_atoi(tmp_tokens->next_token->data);
		printf("%d", exit_status);
	}
	exit(exit_status);
}
