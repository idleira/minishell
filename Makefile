GREEN = \033[0;92;1m
YELLOW = \033[0;33;1m
PINK = \033[0;95;1m
BLUE = \033[0;94;1m
DEF_COLOR = \033[0;37m

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = src/lexer/lexer.c \
       src/parser/parser_cmd_util.c \
       src/parser/parser_utils.c \
       src/lexer/lexer_utils.c \
       src/parser/parser_cmd.c \
       src/parser/parser_utils_list.c \
       src/lexer/lexer_utils_list.c \
       src/parser/parser_error.c \
       src/minishell_utils.c \
       src/parser/parser_traverse.c \
       src/minishell.c \
       src/parser/parser.c \
       src/prompt.c \
	   src/execution/executor.c \
	   src/execution/executor_utils.c \
       src/execution/set_env.c \
	   src/execution/cd.c \
	   src/builtin/export.c \
	   src/builtin/export_utils.c \
	   src/builtin/echo.c \
	   src/builtin/unset.c \
	   src/signals/signals.c \
	   src/builtin/export_sort.c \

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a
DESTRUCTOR_DIR = ./destructor
FT_ALLOC = ./destructor/ft_alloc.a

all: $(LIBFT) $(FT_ALLOC) $(NAME)

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
