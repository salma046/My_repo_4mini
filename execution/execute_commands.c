#include "../minishell.h"

char *find_command_path(char *command, t_env *env) 
{
    char *path_env = NULL;
    char full_path[1024];
    int i = 0, j = 0, k = 0;

    if (ft_strchr(command, '/') != NULL) 
    {
        if (access(command, X_OK) == 0)
            return (command);
        return NULL;
    }
    
	path_env = ft_getenv("PATH", env);

    if (!path_env) {
        errno = ENOENT;
        perror("PATH not found");
        return NULL;
    }

    i = 0;
    while (path_env[i] != '\0') 
    {
        ft_memset(full_path, 0, sizeof(full_path));
        k = 0;

        while (path_env[i] != ':' && path_env[i] != '\0') {
            full_path[k++] = path_env[i++];
        }
        full_path[k++] = '/';

        j = 0;
        while (command[j] != '\0') {
            full_path[k++] = command[j++];
        }
        full_path[k] = '\0';


        if (access(full_path, X_OK) == 0) {
            // printf("Executable found: %s\n", full_path);
            return ft_strdup(full_path);
        }
        if (path_env[i] == ':')
            i++;
    }
    errno = ENOENT;
    // fprintf(stderr, "No executable found for: %s\n", command);
    return NULL;
}
