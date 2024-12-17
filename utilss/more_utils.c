#include "../minishell.h"

void	dup2_mystd_files(int in_fd, int in_fd2)
{
	dup2(in_fd, 0);
	dup2(in_fd2, 1);
	close(in_fd);
	close(in_fd2);
}