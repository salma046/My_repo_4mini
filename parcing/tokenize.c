/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 09:53:45 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/16 12:21:27 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_skipp_spaces(char **line)
{
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == '\v'
		|| **line == '\r')
	{
		(*line)++;
	}
	if (**line == '\0')
		return (1);
	return (0);
}

int	check_separ(const char *line)
{
	if (ft_strncmp(line, "|", 1) == 0)
		return (1);
	else if (ft_strncmp(line, ">>", 2) == 0)
		return (4);
	else if (ft_strncmp(line, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(line, ">", 1) == 0)
		return (3);
	else if (ft_strncmp(line, "<", 1) == 0)
		return (5);
	return (0);
}

int	ft_put_word_token(char **line, enum e_token_type token_t,
		t_token **tokens_list, int heredoc)
{
	char	*word;
	char	*new_word;
	int		i;

	(void)token_t;
	word = *line;
	i = 0;
	if (!process_word_segment(line, &i))
		return (0);
	new_word = get_word(word, i);
	while (is_space(*line) == 1)
		(*line)++;
	token_new_word(new_word, WORD, tokens_list, heredoc);
	return (i);
}

t_token	*ft_tokenize(t_minishell g_minishell)
{
	t_token	*tokens_list;
	char	*line;
	int		herdoc;
	int		sep_type;

	tokens_list = NULL;
	herdoc = -1;
	sep_type = 0;
	line = g_minishell.command;
	while (*line)
	{
		if (ft_skipp_spaces(&line) == 1)
			return (tokens_list);
		sep_type = check_separ(line);
		if (sep_type != 0)
			ft_put_token(&line, sep_type, &tokens_list, &herdoc);
		else
		{
			if (ft_put_word_token(&line, WORD, &tokens_list, herdoc) == 0)
				return (NULL);
			herdoc = -1;
		}
	}
	return (tokens_list);
}
