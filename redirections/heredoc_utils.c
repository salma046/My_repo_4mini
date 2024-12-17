/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:05:50 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/17 11:28:34 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mystructs2(void)
{
	fre_the_tokens(g_minishell.tokens);
	free_env_list(g_minishell.envir);
	free_env_list(g_minishell.export_env);
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

static void	handle_heredoc_line(int fd, char *line, char *limiter,
		t_token *token)
{
	if (!ft_strncmp(line, limiter, ft_strlen(limiter))
		&& (ft_strlen(line) == ft_strlen(limiter)))
	{
		free_mystructs2();
		exit(g_minishell.exit_status = 0);
	}
	if (ft_strncmp(line, limiter, ft_strlen(limiter)))
	{
		if (!line)
			line = ft_strdup("");
	}
	if (token->quotes_heredoc == 0)
	{
		line = rmp_dollar(line, NULL);
	}
	ft_putendl_fd(line, fd);
	if (strcmp(line, limiter))
		free(line);
}

int	ft_start_heredoc_child(int fd, char *limiter, t_token *token)
{
	char	*line;
	char	*missing_lim;
	char	*missing_lim2;

	missing_lim = "bash: warning: here-document at line 5";
	missing_lim2 = " delimited by end-of-file (wanted `";
	signal(SIGINT, sig_here_doc);
	line = readline("> ");
	while (line)
	{
		handle_heredoc_line(fd, line, limiter, token);
		line = readline("> ");
	}
	g_minishell.exit_status = 0;
	ft_putstr_fd("bash: warning: here-document at ", 2);
	ft_putstr_fd("line 5 delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(limiter, 2);
	ft_putstr_fd("')\n", 2);
	close(fd);
	free_mystructs2();
	exit(g_minishell.exit_status);
}
