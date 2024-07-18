# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 14:39:15 by mzhukova          #+#    #+#              #
#    Updated: 2024/07/18 17:43:40 by mzhukova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS	= ft_destructors.o ft_allocs.o ft_utils.o ft_init.o
SOURCE	= ft_destructors.c ft_allocs.c ft_utils.c ft_init.c
HEADER	= ft_alloc.h
OUT	= ft_alloc.a
CC	 = cc
FLAGS	 = -g -c -Wall -Wextra -Werror
LFLAGS	 = 

all: $(OUT)

$(OUT): $(OBJS)
	ar rcs $(OUT) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OUT)

re: fclean all

.PHONY: all clean fclean
