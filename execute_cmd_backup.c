#include "../minishell.h"

char    *find_command_path(char *command, char *env){

        // printf("\033[0;31mcommand:%s\033[0m\n", command);
        // char *path_env = NULL;
        char full_path[1024];
        int i = 0, j = 0, k = 0;

      

        if (!env) {
            errno = ENOENT;
            // perror("PATH not found");
            return NULL;
        }
        i = 0;
        while (env[i] != '\0') 
        {
            ft_memset(full_path, 0, sizeof(full_path));
            k = 0;

            while (env[i] != ':' && env[i] != '\0') {
                full_path[k++] = env[i++];
            }
            full_path[k++] = '/';
            // printf("full_path:%s\n", full_path);
            j = 0;
            while (command[j] != '\0') {
                full_path[k++] = command[j++];
            }
            printf("====>full_path:%s\n", full_path);
            full_path[k] = '\0';

            if (access(full_path, X_OK) == 0) {
                return ft_strdup(full_path);
            }
            if (env[i] == ':')
                i++;
        }
        errno = ENOENT;
    return NULL;
}

int ft_count(t_token *tokens)
{
    t_token *current;
    int i;

    i = 0;
    current = tokens;
    while (current != NULL) {
        i++;
        current = current->next_token;
    }
    return (i);
}

char *return_the_path(t_env *env)
{
    t_env *tmp = env;
    while (tmp) {
        if (!ft_strcmp(tmp->key, "PATH"))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

int ft_execute(t_token *data, t_env *env) {
    char *command_path;
    char **args;
    int arg_count = ft_count(data);
    t_token *current = data;
    int i = 0;

    int x = 0;
    while (env->key[x])
    {
        printf("")
        env = env->next
    }
    
    char *envir = ft_strjoin("PATH=", return_the_path(env));
    
    // char *term_env = getenv("TERM");
    // if (!term_env) {
    //     term_env = "xterm-256color"; // Default if not set.
    // }
    // char *term_var = ft_strjoin("TERM=", term_env);
    char *environ[] = {envir, NULL};

    args = malloc((arg_count + 1) * sizeof(char *));
    if (!args) {
        perror("malloc");
        free(envir);
        return -1;
    }

    while (i < arg_count) {
        args[i++] = current->data;
        current = current->next_token;
    }
    args[arg_count] = NULL;

    command_path = find_command_path(args[0], return_the_path(env));
    if (!command_path) {
        printf("%s: command not found\n", args[0]);
        free(args);
        free(envir);
        return 127;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork");
        free(command_path);
        free(args);
        free(envir);
        return -1;
    } else if (pid == 0) {
        if (execve(command_path, args, environ) == -1) {
            perror("execve");
            free(command_path);
            free(args);
            free(envir);
            exit(1);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (status >> 8 != 0) {
            perror("Command execution failed");
        }
    }

    free(command_path);
    free(args);
    free(envir);
    return 0;
}

