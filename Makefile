GREEN = \033[0;92;1m
YELLOW = \033[0;33;1m
PINK = \033[0;95;1m
BLUE = \033[0;94;1m
DEF_COLOR = \033[0;37m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	src/lexer/lexer.c			src/parser/quotes.c					src/prompt.c \
		src/lexer/lexer_utils.c		src/parser/var_expander.c			src/minishell.c \
		src/builtin/env_get.c		src/parser/var_expander_util.c		src/free_pointers.c \
		src/builtin/env_init.c

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -lreadline -o $@
	@echo "$(PINK)✿◕ ‿ ◕✿$(DEF_COLOR) minishell compiled successfully."

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
	@echo "$(YELLOW)✧･ﾟ:* (っ◕‿◕)っ :ﾟ･✧$(DEF_COLOR) minishell cleaned."

re: fclean all

.PHONY: all clean fclean re
