#include "../minishell.h"

int	ft_cd(t_minishell *data)
{
	t_token	*tmp_tokens;

	tmp_tokens = data->tokens;
	while (tmp_tokens)
	{
		if (!ft_strcmp(tmp_tokens->data, "cd")
			&& tmp_tokens->next_token == NULL)
		{
			if (chdir(getenv("HOME")) == -1)
				perror("cd");
			printf("Home path:  \033[0;31m%s\033[0m\n", getenv("HOME"));
		}
		if (!ft_strcmp(tmp_tokens->data, "cd") && tmp_tokens->data)
		{
			printf("This is the path of cd:%s\n", getenv("HOME"));
			if (tmp_tokens->next_token && chdir(tmp_tokens->next_token->data)
				== -1)
				perror("\033[32m ERROR\033[0m");
			else
				printf("DONE ✅\n");
		}
		tmp_tokens = tmp_tokens->next_token;
	}
	return (0);
}
