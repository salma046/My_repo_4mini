/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 09:53:45 by salaoui           #+#    #+#             */
/*   Updated: 2024/12/08 14:06:15 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_skipp_spaces(char **line)
{
	while (**line == ' ' || **line == '\t' || **line == '\n' || **line == 'v'
		|| **line == '\r')
	{
		(*line)++;
	}
	if (**line == '\0')
		return (1);
	return (0);
}

t_token	*ft_tokenize(t_minishell g_minishell)
{
	t_token	*tokens_list;
	char	*line;
	int		herdoc;

	tokens_list = NULL;
	herdoc = -1;
	line = g_minishell.command;
	while (*line)
	{
		if (ft_skipp_spaces(&line) == 1)
			return (tokens_list);
		if (ft_strncmp(line, "|", 1) == 0)
			ft_put_token(&line, PIPE, &tokens_list);
		else if (ft_strncmp(line, ">>", 2) == 0)
			ft_put_token(&line, APPEND, &tokens_list);
		else if (ft_strncmp(line, "<<", 2) == 0)
		{
			ft_put_token(&line, HER_DOC, &tokens_list);
			herdoc = 1;
		}
		else if (ft_strncmp(line, ">", 1) == 0)
			ft_put_token(&line, OUT_REDIR, &tokens_list);
		else if (ft_strncmp(line, "<", 1) == 0)
			ft_put_token(&line, INP_REDIR, &tokens_list);
		else
		{
			if (ft_put_word_token(&line, WORD, &tokens_list, herdoc) == 0)
				return (NULL);
			herdoc = -1;
		}
	}
	return (tokens_list);
}
