#include "../minishell.h"

int	**free_fd(int **fd, int count)
{
	count--;
	while (count >= 0)
	{
		free(fd[count]);
		count--;
	}
	free(fd);
	return (NULL);
}

int	**mksome_files(int count_pipe)
{
	int		**fd;
	int		i;

	i = 0;
	if (count_pipe == 1 || count_pipe == 0)
		return (NULL);
	fd = (int **)malloc(sizeof(int *) * (count_pipe));
	if (!fd)
		return (NULL);
	while (i < count_pipe - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return(free_fd(fd, i));
		pipe(fd[i]);
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

int	assign_files(t_minishell data, t_node *nodes)
{
	t_node	*tmp_node;
	int		**file;
	int		i;

	i = 1;
	if (data.files == NULL)
		return (0);
	tmp_node = nodes;
	file = data.files;
	tmp_node->out_file = file[0][1];
	tmp_node = tmp_node->next_node;
	while (tmp_node)
	{
		if (file[i] == NULL)
		{
			tmp_node = tmp_node->prev_node;
			tmp_node->in_file = file[i - 1][0];
			tmp_node->out_file = 1;
			return (0);
		}
		tmp_node->in_file = file[i - 1][0];
		tmp_node->out_file = file[i][1];
		tmp_node = tmp_node->next_node;
		i++;
	}
	tmp_node = tmp_node->prev_node;
	tmp_node->in_file = file[i - 1][0];// for the last node will give it only from
					// where to take the in and the out will be the default(terminal);
	tmp_node->out_file = 1;
	return (0);
}
