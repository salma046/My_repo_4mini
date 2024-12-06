#include "../minishell.h"

void free_env_array(char **arr)
{
    int i = 0;

    if (!arr)
        return;

    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}