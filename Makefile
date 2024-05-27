GREEN = \033[0;92;1m
YELLOW = \033[0;33;1m
PINK = \033[0;95;1m
BLUE = \033[0;94;1m
DEF_COLOR = \033[0;37m

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =  src/lexer/lexer.c					src/parser/parser_cmd_util.c					src/parser/parser_utils.c		\
		src/lexer/lexer_utils.c				src/parser/parser_cmd.c							src/parser/parser_utils_list.c	\
		src/lexer/lexer_utils_list.c		src/parser/parser_error.c						src/minishell_utils.c			\
		src/builtin/env_get.c				src/parser/parser_iterate.c						src/minishel.c 					\
		src/builtin/env_init.c				src/parser/parser.c								src/prompt.c

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -lreadline -o $@
	@echo "$(PINK)꒰ᐢ. .ᐢ꒱$(DEF_COLOR) minishell compiled successfully!"

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
	@echo "$(YELLOW)✧･ﾟ:* ꒰ᐢ. .ᐢ꒱ :ﾟ･✧$(DEF_COLOR) minishell cleaned!"

re: fclean all

git:
	@git add .
	@git commit -m "$m"
	@git push
	
.PHONY: all clean fclean re
