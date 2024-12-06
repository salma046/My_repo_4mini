#include "../minishell.h"

int	ft_start_heredoc(int fd, char *limiter)
{
	char	*line;

	line = readline("heredoc>");
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& (ft_strlen(line) == ft_strlen(limiter)))
		{
			free(line);
			return (close(fd), 0);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			if (!line)
				line = ft_strdup("");
		}
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("heredoc>");
	}
	return (0);
}

int	start_heredoc(int fd, char *limiter)
{
	if (!limiter)
		return (-1);
	if (ft_start_heredoc(fd, limiter) < 0)
		return (-1);
	return (0);
}

void	change_value(t_token *token, char *filename)
{
	token->data = NULL;
	token->data_type = INP_REDIR;
	token->next_token->data = filename;
	token->next_token->data_type = WORD;
}

int	ft_heredoc(t_token *tokens)
{
	char	*limiter;
	char	*file;
	int		fd;

	file = "/tmp/heredoc.txt";
	if (unlink(file) == -1)
		dprintf(2, "no file found 2be del\n");
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_EXCL, 0644);
	if (fd < 0)
		return (-1);
	if (tokens->next_token->data_type == WORD)
	{
		limiter = tokens->next_token->data;
		if (start_heredoc(fd, limiter) < 0)
			return (close(fd), -1);
		else
			return (close(fd), change_value(tokens, file), 1);
	}
	else
		return (close(fd), -1);
	return (0);
}

int	main_heredoc(t_token *tokens)
{
	t_token	*temp_tokens;

	temp_tokens = tokens;
	while (temp_tokens)
	{
		if (temp_tokens->data_type == HER_DOC && temp_tokens->next_token
			&& ft_heredoc(temp_tokens) == -1)
		{
			return (-1);
		}
		temp_tokens = temp_tokens->next_token;
	}
	return (0);
}
