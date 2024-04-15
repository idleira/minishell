/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:15:42 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/15 17:58:55 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_word	t_word;

typedef struct s_split
{
	int		cmds;
	t_word	*first;
	t_word	*last;
}	t_split;

typedef struct s_word
{
	char			*content;
	int				index;
	int				type;
	struct s_word	*next;
	struct s_word	*prev;
}	t_word;

typedef enum e_word_type
{
	CMD,
	OPERATOR,
	FLAG,
	REDIR,
	PATH,
	PIPE,
	QUOTE,
	ARG,
	STR,
}	t_word_type;


//creating tokens and stuff
t_word *new_token(char *content, int index, t_word_type type);
t_word *create_token(t_split *tokens, char *start, int i, t_word_type type);
void handle_token(t_split *tokens, char **start, char *s, int *i, t_word_type type);
t_split *tokenize(char *s);

//utils
int	is_space(char c);
int	is_symbol(char c);
int	is_quote(char c);
void skip_space(char *input, int *j);
void skip_quotes(int *i, char *input);

#endif