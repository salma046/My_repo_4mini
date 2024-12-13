#include "../minishell.h"

void	free_mystructs2()
{
	fre_the_tokens(g_minishell.tokens);
	free_env_list(g_minishell.envir);
	free_env_list(g_minishell.export_env);
	// free_node_list(g_minishell.nodes);
}

void	sig_here_doc(int signal)
{
	(void)signal;
	close(g_minishell.exit_status);
	write(1, "\n", 1);
	g_minishell.exit_status = 130;
	free_mystructs2();
	exit(g_minishell.exit_status);
}

int	ft_start_heredoc_child(int fd, char *limiter, t_token *token)
{
	char	*line;

	signal(SIGINT, sig_here_doc);
	line = readline("heredoc>");
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& (ft_strlen(line) == ft_strlen(limiter)))
		{
			free_mystructs2();
			exit (g_minishell.exit_status = 0);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			if (!line)
				line = ft_strdup("");
		}
		if (token->quotes_heredoc == 0)
		{
			line = rmp_dollar(line, NULL, 0);
		}
		ft_putendl_fd(line, fd);
		if (strcmp(line, limiter))
			free(line);
		line = readline("heredoc>");
	}
	printf("missing limiter\n");
	close(fd);
	free_mystructs2();
	exit(g_minishell.exit_status);
}

int	ft_start_heredoc(int fd, char *limiter, t_token *token)
{
	pid_t pid;
	int status;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
		ft_start_heredoc_child(fd, limiter, token);
	waitpid(pid, &status, 0);
	close(fd);
	if (WIFEXITED(status))
		g_minishell.exit_status = WEXITSTATUS(status);
	return (g_minishell.exit_status);
}

int	start_heredoc(int fd, char *limiter, t_token *token)
{
	if (!limiter)
		return (-1);
	return (ft_start_heredoc(fd, limiter, token));
}

void	change_value(t_token *token, char *filename)
{
	token->data = NULL;
	token->data_type = INP_REDIR;
	free(token->next_token->data);
	token->next_token->data = ft_strdup(filename);
	token->next_token->data_type = WORD;
}

int	ft_heredoc(t_token *tokens)
{
	char	*limiter;
	char	*file;
	int		fd;

	file = "/tmp/heredoc.txt";
	unlink(file);
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_EXCL, 0644);
	if (fd < 0)
		return (-1);
	if (tokens->next_token->data_type == WORD)
	{
		limiter = tokens->next_token->data;
		start_heredoc(fd, limiter, tokens->next_token);
		if (g_minishell.exit_status == 130)
		{
			fprintf(stderr, "Hello World\n");
			unlink(file);
			return (-1);
		}
		fd = open("/tmp/heredoc.txt", O_RDONLY);
		file = "/tmp/heredoc.txt";
		change_value(tokens, file);
	}
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
