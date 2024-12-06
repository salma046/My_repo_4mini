#include "minishell.h"

void ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}