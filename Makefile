# Colors:
RED = \033[0;31m
YELLOW = \033[0;33m
BLACK = \033[0m
MAGENTA = \033[1;35m
CYAN = \033[36m
GREEN0 = \033[32m
GREEN1 = \033[38;5;121m

# Files:
SRC = parcing/parsing.c parcing/handle_quotes.c parcing/nodes.c parcing/nodes_utils.c \
      expend/dollar.c expend/expend_utils.c parcing/tokenize_utils.c parcing/tokenize.c \
      builtins/checking_cmd.c builtins/ft_cd.c builtins/ft_echo.c builtins/ft_env.c \
      builtins/ft_pwd.c builtins/ft_exit.c builtins/ft_unset.c builtins/ft_export.c \
      redirections/heredoc.c redirections/open_files.c execution/ft_execution.c \
      redirections/ft_redirections.c expend/expend_utils3.c utilss/libft_utils.c \
      utilss/sjd_fun_utils.c execution/execute_commands.c expend/expend_utils2.c \
      minishell.c expend/expend_utils4.c expend/expend_utils5.c free/free_nodes.c \
	  utilss/ft_export_utils.c utilss/export_utils2.c print_error.c free_leaks/free_leaks_1.c \
	  utilss/export_utils.c utilss/ctrl.c
	  

OBJ = $(SRC:.c=.o)

# Flags:
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address -g3

# Library:
NAME = minishell
LIBFT = libft.a

# Targets:
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(CYAN)Making minishell..👾$(BLACK)"
	@$(CC) $(OBJ) $(LIBFT) $(CFLAGS) -lreadline -o $(NAME)

$(LIBFT):
	@make -C libft
	@mv libft/libft.a .

clean:
	@echo "$(GREEN0)Cleaning 🧹$(BLACK)"
	@rm -rf $(OBJ)
	@make -C libft clean
	@rm -rf $(LIBFT)

fclean: clean
	@rm -rf $(NAME)
	@echo "$(YELLOW)Done cleaning ✨$(BLACK)"

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
