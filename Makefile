GREEN = \033[0;92;1m
YELLOW = \033[0;33;1m
PINK = \033[0;95;1m
BLUE = \033[0;94;1m
DEF_COLOR = \033[0;37m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS =	src/prompt.c \
		src/lexer/scanner.c \
		src/lexer/scanner_utils.c \
		src/lexer/lexer.c \
		src/lexer/lexer_utils.c \
		src/lexer/lexer_utils_list.c \
		src/parser/parser.c \
		src/parser/parser_utils.c \
		src/parser/parser_error.c \
		src/parser/parser_utils_list.c \
		src/execution/executor.c \
		src/execution/executor_utils.c \
		src/execution/set_env.c \
		src/execution/cd.c \
		src/execution/errors.c \
		src/execution/exits.c \
		src/execution/execute_pipeline.c \
		src/builtin/export.c \
		src/builtin/export_utils.c \
		src/builtin/echo.c \
		src/builtin/heredoc.c \
		src/builtin/unset.c \
		src/builtin/export_sort.c \
		src/signals/signals.c \
		src/traverse.c \
		src/minishell.c \
		src/minishell_utils.c \
		src/minishell_utils_2.c \

LIBFT_DIR = ./libft
FT_ALLOC = ./destructor/ft_alloc.a
LIBFT = ./libft/libft.a
DESTRUCTOR_DIR = ./destructor

all: $(FT_ALLOC) $(LIBFT) $(NAME)

$(FT_ALLOC):
	@$(MAKE) -sC $(DESTRUCTOR_DIR)

$(LIBFT):
	@$(MAKE) bonus -sC $(LIBFT_DIR)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(FT_ALLOC) -lreadline -o $@
	@echo "$(PINK)꒰ᐢ. .ᐢ꒱$(DEF_COLOR) minishell compiled successfully!"

clean:
	@$(MAKE) clean -sC $(LIBFT_DIR)

fclean: clean
	@$(MAKE) fclean -sC $(LIBFT_DIR)
	@$(MAKE) fclean -sC $(DESTRUCTOR_DIR)
	@rm -rf $(NAME)
	@echo "$(YELLOW)✧･ﾟ:* ꒰ᐢ. .ᐢ꒱ :ﾟ･✧$(DEF_COLOR) minishell cleaned!"

re: fclean all

git:
	@git add .
	@git commit -m "$m"
	@git push
	
.PHONY: all clean fclean re
