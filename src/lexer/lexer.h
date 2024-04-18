/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:15:42 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/18 17:56:45 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
#include "../../libft/libft.h"

typedef enum e_word_type
{
    CMD,
    ARG,
    OPER,
    PIPE,
    QUOTE,
}	t_word_type;

typedef struct s_word	t_word;

typedef struct s_split
{
    int		cmds;
    char	*value;
    char	*type;
    t_word	*first;
    t_word	*last;
    t_word *head;
    t_word *tail;
    struct s_split *next;
}	t_split;

typedef struct s_word
{
    char			*content;
    int				index;
    t_word_type		type;
    struct s_word	*next;
    struct s_word	*prev;
}	t_word;

typedef struct s_info
{
    char	**start;
    char	*s;
    int		*i;
}               t_info;

//creating tokens and stuff
t_word	*token_new(char *content, int start, int end, t_word_type type);
t_word	*token_create(t_split *tokens, char *start, int index, t_word_type type);
t_info	*init_info(char **start, char *s, int *i);;
t_word	*create_token(t_split *tokens, char *start, int i, t_word_type type);
void	handle_token(t_split *tokens, char **start, char *s, int *i, t_word_type type);
t_split	*tokenize(char *s);

//utils
int	is_space(char c);
int	is_symbol(char c);
int	is_quote(char c);
void skip_space(char *input, int *j);
void skip_quotes(int *i, char *input);

#endif