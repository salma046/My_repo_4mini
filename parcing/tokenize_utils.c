#include "../minishell.h"

void	token_new_sep(enum e_token_type token_t, t_token **tokens_list)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->data = NULL;
	new_token->data_type = token_t;
	new_token->next_token = NULL;
	ft_lstadd_back_token(tokens_list, new_token);
}

void	ft_put_token(char **line, enum e_token_type token_t,
		t_token **tokens_list)
{
	if (token_t == APPEND)
	{
		token_new_sep(APPEND, tokens_list);
		(*line)++;
	}
	else if (token_t == HER_DOC)
	{
		token_new_sep(HER_DOC, tokens_list);
		(*line)++;
	}
	else
		token_new_sep(token_t, tokens_list);
	(*line)++;
}

void	token_new_word(char *word, enum e_token_type token_t,
		t_token **tokens_list, int heredoc)
{
	t_token	*new_token;
	char	*new_word;
	int		i;

	i = 0;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	if (heredoc < 0)
	{
		new_word = rmp_dollar(word, tokens_list, &i);
	}
	else
		new_word = word;
	new_token->prev_token = NULL;
	new_token->quotes_heredoc = 0;
	new_token->data = new_word;
	new_token->is_ambiguous = i;
	new_token->data_type = token_t;
	new_token->next_token = NULL;
	ft_lstadd_back_token(tokens_list, new_token);
}

int	find_quote(char c, char **line, int *i)
{
	char quote;

	(*line)++;
	(*i)++;
	while (**line != '\0' && ft_strncmp(*line, &c, 1) != 0)
	{
		(*line)++;
		(*i)++;
	}
	quote = **line;
	if (quote == c)
		return (1);
	return (0);
}

int	ft_put_word_token(char **line, enum e_token_type token_t,
		t_token **tokens_list, int heredoc)
{
	(void)token_t;
	char	*word;
	char	*new_word;
	char	quote;
	int		i;

	word = *line;
	i = 0;
	while (**line != '\0' && ft_strncmp(*line, ">", 1) != 0 && ft_strncmp(*line, "<", 1) != 0 && ft_strncmp(*line, "|", 1) != 0 && is_space(*line) == 0)
	{
		if (**line == '&')
		{
			printf("syntkax error\n");
			return (0);
		}
		if (**line == '"' || **line == '\'')
		{
			quote = **line;
			if (find_quote(**line, line, &i) == 0)
			{
				printf("syntax error missing %c\n", quote);
				return (0);
			}
		}
		i++;
		(*line)++;
	}
	new_word = get_word(word, i);
	while (is_space(*line) == 1)
		(*line)++;
	token_new_word(new_word, WORD, tokens_list, heredoc);
	return (i);
}
