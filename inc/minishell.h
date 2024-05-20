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

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
//# include <readline/readline.h>
//# include <readline/history.h>
# include <limits.h>
# include <dirent.h>

// struct used by the lexer
typedef struct s_lexer
{
	int		i;
	int		j;
	int		param_exp;
	char	*line;
	int		error;
	char	quote;
	char	**tokens;
	char	*cmd;
}	t_lexer;

// struct used by the prompt string
typedef struct s_prompt
{
	char	*line;
}	t_prompt;

// struct used by the parser

typedef struct s_parser
{
	int		param_exp;
	char	**tokens;
	char	**req;
	char	*p_match;
	char	*matched;
	int		first;
	int		last;
	int		wc_present;
	int		i;
	int		j;
	char	*line;
	char	**tokens2;
	char	quote;
}	t_parser;

typedef enum e_types
{
	__RED_IN,
	__RED_OUT,
	__RED_APP,
	__HEREDOC,
	__PIPE,
	__COMMAND,
	__OR,
	__AND,
	__SUBSHELL,
	__NONE
}	t_types;

typedef struct s_info
{
	char			*full_cmd;
	t_types			op;
	struct s_info	*next;
}	t_info;

//lexer functions
int		quotes_check(t_lexer *lexer, char *s);
int		operators_separate(t_lexer *lexer, char *s);
int		input_process(char *s, t_lexer *lexer);
char	**tokenise(t_lexer *lexer);

//lexer utility
void	tokens_print(char **tokenise);
void	array_free(char **arr);

//parser functions
void	quotes_strip(t_parser *parser, char *s);
void	quotes_process(t_parser *parser);

#endif