#include "../minishell.h"

void ft_print(t_node *node)
{
    int i = 0;
    
    while (node->cmd[i])
    {
        write(1, node->cmd[i], ft_strlen(node->cmd[i]));
        if (node->cmd[i + 1] != NULL)
            write(1, " ", 1);
        i++;
    }
}

void ft_check_n_flag(char **cmd, int *flag, int *start)
{
    *flag = 0;
    *start = 1;

    while (cmd[*start] && strncmp(cmd[*start], "-n", 2) == 0)
    {
        char *str = cmd[*start];
        int i = 2;  
        int all_n = 1;  

        while (str[i] != '\0')
        {
            if (str[i] != 'n')
            {
                all_n = 0;  
                break;
            }
            i++;
        }
        if (all_n)
        {
            *flag = 1;
            (*start)++;
        }
        else
            break;
    }
}

void ft_echo(t_node *node)
{
    int flag = 0;
    int start_index = 1;

    if (!node->cmd || !node->cmd[1])
    {
        write(1, "\n", 1);
        return;
    }

    ft_check_n_flag(node->cmd, &flag, &start_index);

    if (!node->cmd[start_index])
        return;

    int i = start_index;
    while (node->cmd[i])
    {
        write(1, node->cmd[i], ft_strlen(node->cmd[i]));
        if (node->cmd[i + 1] != NULL)
            write(1, " ", 1);
        i++;
    }
    if (!flag)
        write(1, "\n", 1);
}

