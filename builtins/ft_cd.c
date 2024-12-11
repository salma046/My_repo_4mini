/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:56:34 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/10 15:47:44 by salaoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_home(char *str)
{
	char	*home_path;

	home_path = getenv("HOME");/// you should use our env
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
	while (tmp_node)
	{
		// you should not loop through the args
		// if one arg ==> go to the home if home is found on our env
		// if two args==> check if dir is found go to it if not printf error on stderror
		// else more than two do fprintf(stderr, "too many arguments\n");
		i = 0;
		while (tmp_node->cmd && tmp_node->cmd[i])
		{
			if (ft_strcmp(tmp_node->cmd[i], "cd") == 0)
			{
				if (!tmp_node->cmd[i + 1])
				{
					printf("hwllo\n");
					return (ft_cd_home(tmp_node->cmd[i]));
				}
				return (ft_cd_path(tmp_node->cmd[i + 1]));
			}
			i++;
		}
		tmp_node = tmp_node->next_node;
	}
	return (0);
}
