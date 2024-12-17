#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char			*value;
	char			*key;
	struct s_env	*next;
}					t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
	HER_DOC,
	OUT_REDIR,
	APPEND,
	INP_REDIR
}					t_token_type;

typedef struct s_token
{
	int				is_ambiguous;
	int				quotes_heredoc;
	char			*data;
	t_token_type		data_type;
	struct s_token	*next_token;
	struct s_token	*prev_token;
	char			**envirement;
}					t_token;

typedef struct s_redir
{
	t_token_type		red_type;
	char			*file;
	int				is_ambiguous;
	struct s_redir	*next;
}					t_redir;

typedef struct s_node
{
	char			**cmd;
	t_redir			*redir;
	int				out_file;
	int				in_file;
	int				is_ambiguous;
	struct s_node	*next_node;
	struct s_node	*prev_node;
}					t_node;

typedef struct s_minishell
{
	char			**envirement;
	char			*command;
	int				count_pips;
	int				exit_status;
	int				**files;
	// int				is_ambiguous;
	pid_t			g_pid;
	t_env			*envir;
	t_env			*export_env;
	t_token			*tokens;
	t_node			*nodes;
}					t_minishell;

extern t_minishell	g_minishell;

char				**mk_tenv_char(t_env *envir);
char				*get_word(char *str, int i);
char				*get_env_var(char *str, int i);
char				*fill_first_part(char *env_var, int *i);
char				*fill_middle_part(char *env_var, int *i);
char				*allocate_4_nword(char *str, char *env_var);
char				*ft_join_words(char *word, char *str, int l);
char				*remplace_doll_str(char *data, char *env_var);
char				*after_dol_word(char *str, int l, int str_len);
char				*rmp_dollar(char *tokens_word, t_token **tokens_list);
char				*rmp_dollar2(char *t_word, int *i, int to_split,
						t_token **tokens_list);
char				*token_edi_env(char *str, char *env_var,
						t_token **tokens_list);
int					is_space(char *line);
int					cmd_count(t_token *tokens);
int					count_pipe(t_node *nodes);
int					check_4_space(char *env_var);
int					valid_word(char *str, int i);
int					count_dollar_lenth(char *str);
int					check_is_num(char *str, int i);
int					count_lenth2(char *str, int *i);
int					is_not_valid_expend(char *str, int i);
int					put_env_in_word(char *str, char *word, char *env_var,
						int *i, int *j);
int					ft_put_word_token(char **line, enum e_token_type token_t,
						t_token **tokens_list, int heredoc);
void				free_node(t_node *node);
void				free_redir_list(t_redir *redir);
char				*free_arr(char **arr, int i);
void				free_node_list(t_node *node_list);
void				skip_double_signs(char *str, int *i);
void				skip_quo(char *tokens_word, int *i, int quot);
void				skip_2quo(char *tokens_word, int *i, int quot);
void				skip_if_isalnum(char *tokens_word, int *i);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
void				skip_double_quo(char *tokens_word, int *to_split, int *i);
void				fill_word_sgl_quot(char *word, char *str, int *i, int *j);
void				ft_redi_add_back(t_redir **redirections,
						t_redir *new_redir);
void				fill_redi(enum e_token_type token_t, char *red_file,
						t_redir **redirections, int is_true);
void				token_new_edi_word(char *word, enum e_token_type token_t,
						t_token **tokens_list);
void				ft_put_token(char **line, enum e_token_type token_t,
						t_token **tokens_list, int *heredoc);
void				token_new_word(char *word, enum e_token_type token_t,
						t_token **tokens_list, int heredoc);
t_token				*ft_tokenize(t_minishell g_minishell);
t_token				*rm_qotes(t_token *tokens);
t_token				*parsing(t_minishell g_minishell);
t_node				*mk_nodes(t_token *tokens);
t_node				*allocate_for_node(t_token *temp_tokens);
void				free_env_list(t_env *head);
void				fre_the_tokens(t_token *tokens);
char				*ft_getenv(char *key, t_env *envir);
void				free_mystructs(void);
// functionts utils ✙:
char				*ft_strncpy(char *dst, const char *src, size_t len);
int					ft_strcmp(char *s1, char *s2);

// building 🏗️:
int					ft_cd(t_minishell *data);
void				ft_pwd(t_node *node);
void				ft_echo(t_node *node);
int					ft_env(char **cmds, t_minishell *data);
void				ft_exit(t_node *nodes);
void				ft_unset(t_minishell *data);
int					ft_export(t_minishell *data, t_env *expo_envir,
						t_env *env_envir);
int					search_special_char(char *token_data, t_node *node);
int					ft_add_to_export_arg(t_node *nodes, t_env *expo_envir,
						t_env *env_envir);
int					is_special_char(char c);
int					has_doubled_special_chars(char *token);

// commands 🗣️:
t_env				*mk_env(char **envirement);
t_env				*ft_env_unset(t_minishell *data);
int					check_key(char *str, t_env *envir);
int					ft_check_builtins(char *command);
char				*put_quot2_value(char *str);
char				*rm_quot2_value(char *str);
int					check_command(t_minishell *data, t_node *node);
int					ft_env_export_once(t_node *nodes, t_env *envir, int active);
void				key_without_equal(char *data, t_env *envir);
void				key_with_equal(char *data, t_env *envir);
void				remove_node(t_env **head, char *keyToRemove);
void				search_check_add_env(t_env *expo_envir, t_env *env_envir);
void				*mk_env_4expo(char **envir);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*is_valid_cmd(char *cmd);
char				*find_command_path(char *command, t_env *env);
void				add_struc_2_env(t_env *expo_env, t_env *envir);
// execute commands 🚀:
int					ft_execute_one_cmd(t_minishell data);
int					ft_execute_multi_cmd(t_minishell data, int red_result);
// redirectios 🔁:
int					ft_input(char *file_name, t_node *node);
int					ft_output(char *file_name, t_node *node);
int					ft_append(char *file_name, t_node *node);
int					ft_check_redirections(t_node *nodes);
int					main_heredoc(t_token *tokens);
int					ft_heredoc(t_token *tokens);
int					start_heredoc(int fd, char *limiter, t_token *token);
int					ft_start_heredoc_child(int fd, char *limiter, t_token *token);
int					process_word_segment(char **line, int *i);

void				dup_my_files(t_node *temp_nodes);
void				dup2_mystd_files(int in_fd, int in_fd2);

// signals
void				clean_multi_cmd(pid_t pid, t_minishell data);
void				signals_pid(pid_t pid);
void				handle_sigint(int sig);
void				handle_child(int sig);

#endif
