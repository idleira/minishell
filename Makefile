GREEN = \033[0;92;1m
YELLOW = \033[0;33;1m
PINK = \033[0;95;1m
BLUE = \033[0;94;1m
DEF_COLOR = \033[0;37m

NAME	= minishell

CC		= @cc
CFLAGS	= -Werror -Wall -Wextra -pthread

LIBFT =	./libft/libft.a

SRC_DIR = ./src/lexer/
SRC		=	lexer.c 	lexer_utils.c

OBJ_DIR = ./obj/lexer/
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME) $(LIBFT)

$(LIBFT):
	@make $(NOPR) $(LIBFT)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $@
	@echo "૮꒰ྀི∩´ ᵕ \`∩꒱ྀིა \"ᵐᶦⁿᶦˢʰᵉˡˡ ᶜᵒᵐᵖᶦˡᵉᵈ\" ⋆｡𖦹 °.🐚⋆❀˖°"
    
clean:
	@rm -rf $(OBJ_DIR) $(LIBFT_DIR)/*.o

fclean: clean
	@rm -f $(NAME) $(LIBFT_DIR)/*.o libft/libft.a
	@echo -e "໒꒰ྀི˶˃ᆺ˂˶ ꒱ྀིა \"ᵐᶦⁿᶦˢʰᵉˡˡ ᶜˡᵉᵃⁿ\" ⋆｡𖦹 °.🐚⋆❀˖°"

re: fclean all

.PHONY: all re clean fclean