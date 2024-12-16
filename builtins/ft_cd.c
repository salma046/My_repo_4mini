/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:56:34 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/15 00:04:52 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_home(char *str)
{
	char	*home_path;

	home_path = getenv("HOME");
	if (!home_path)
	{
		printf("bash: cd:%s HOME not set\n", str);
		return (1);
	}
	if (chdir(home_path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd_path(char *path)
{
	if (chdir(path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd(t_minishell *data)
{
	t_node	*tmp_node;
	int		i;

	tmp_node = data->nodes;
	if (tmp_node->cmd[2])
	{
		write(2, "bash: cd: too many arguments\n", 30);
		return (data->exit_status = 1, 1);
	}
	while (tmp_node)
	{
		i = 0;
		while (tmp_node->cmd && tmp_node->cmd[i])
		{
			if (ft_strcmp(tmp_node->cmd[i], "cd") == 0)
			{
				if (!tmp_node->cmd[i + 1])
					return (ft_cd_home(tmp_node->cmd[i]));
				return (ft_cd_path(tmp_node->cmd[i + 1]));
			}
			i++;
		}
		tmp_node = tmp_node->next_node;
	}
	return (0);
}
