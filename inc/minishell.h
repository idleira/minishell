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
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

// struct for prompt string
typedef struct s_prompt
{
	char	*line;		// the line that the user inputs
}	t_prompt;

// enum for error handling
typedef enum e_error
{
	no_error,
	error_of_single_quotes,
	error_of_double_quotes,
	error_of_pipeline,
	error_of_redirection_in,
	error_of_redirection_out,
	error_of_redirection_append,
	error_of_redirection_heredoc
}	t_error_types;

// struct for error handling
typedef struct s_error
{
	t_error_types	error_type;
	int				exit_staus;
}	t_errors;

// struct for the scanner
typedef struct s_scanner
{
	char	*command;		// raw input from user (echo Hello, World! >> output.txt)
	char	*line;			// processed version, where tokens have been identified and separated (echo\nHello,\nWorld!\n>>\noutput.txt\n)
	char	**tokens;		// array of strings, where each string is a token (echo, Hello,, World!, >>, output.txt)
	int		i;				// index of the current character in the command
	int		j;				// index of the current character in the line
	char	t_quote;		// the type of quote (single or double)
}	t_scanner;

// token types
typedef enum e_types
{
	__WORD = 0,
	__RED_IN = '<',
	__RED_OUT = '>',
	__RED_APP = 15934,
	__HEREDOC,
	__PIPE = '|'
}	t_types;

// token state to check the type of quotes
typedef enum e_state
{
	__d_quotes = '\"',
	__s_quotes = '\'',
	__without_quotes = 0
}	t_state;

// struct for the parser
typedef struct s_parser
{
	char			**args;		// in parse_cmd_list, words that are not redirections or pipes are stored here (so technically not just arg, but cmds for now as well)
	t_list			*file;		// the files assosiated with the command (redirections for now)
	struct s_parser	*next;
	struct s_parser	*prev;		
}	t_parser;

// the struct of doubly linked-list in which we'll store our splitted tokens
typedef struct s_dlist
{
	char			*value;		// the token itself
	t_types			type;		// the type of the token
	t_state			state;		// the state of the token (single/double/ no quotes)
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_env
{
	char *pwd;
	char *old_pwd;
	char *home;
	char **paths;
	char **all_vars;
}	t_env;

// prompt functions
void	prompt_build(t_prompt *prompt);
char	*input_get(t_prompt *prompt);

// scanner functions
void	ft_scanner(t_scanner *scanner);
void	handle_quotes(t_scanner *scanner);
void	handle_operators(t_scanner *scanner);
void	cmds_split(t_scanner *scanner);
void	scanner_free(char **tokens);

// lexer functions
void	ft_lexer(t_dlist **head, t_scanner *scanner);
void	tokenizer(t_dlist **head, char *token);
t_dlist	*node_quotes(char *token, char quote);
t_dlist	*node_redirection(char *token);
t_dlist	*node_pipeline(char *token);
t_dlist	*node_word(char *token);
void	quotes_strip(t_dlist *head, char quote);
void	quotes_remove(t_dlist *head);

// doubly linked list functions for lexer
t_dlist	*node_create_lex(void);
t_dlist	*node_last_lex(t_dlist *head);
void	node_append_lex(t_dlist **head, t_dlist *new);
void	traverse_list(t_dlist *head);
void	node_free(t_dlist *head, int boolean);

// error fucntions
void	ft_error(t_dlist *head, t_errors *error);
void	error_display(t_errors *error);

// minishell functions
int		check_spaces(char *s);
void	ptrs_free(t_prompt *prompt, t_scanner *scanner, t_errors *error);
int		ft_check(t_scanner *scanner, t_prompt *prompt, t_errors *error);
t_parser	*input_process(t_scanner *scanner, t_dlist *head, t_errors *error,
			t_prompt *prompt);

// parser function
void	parse_cmd_list(t_parser **parser, t_dlist *head);
// int		count_files(t_dlist	*head);
int		count_args(t_dlist *head);
// void	assign_file(t_dlist *head, t_parser *node, int i);
void	assign_args(t_dlist *head, t_parser *node, char *args);

// doubly linked list functions for parser
t_parser	*node_create_pars(void);
t_parser	*node_last_pars(t_parser *head);
void	node_append_pars(t_parser **head, t_parser *new);

// traverse functions
void	traverse_lexer(const t_dlist *head);
void	traverse_scanner(char **scanner);
void	traverse_parser(const t_parser *head);

//EXECUTION:
//Executor:
char	*get_path(char *cmd, t_env *env);
void	execute_command(t_parser *cmd, t_env *env);
void	handle_redirection(t_parser *cmd);
void	execute_pipeline(t_parser *head, t_env *env);
void	chose_execution(t_parser *head, t_env *env);
void	free_parser(t_parser *head);
void	free_split(char **split);
char	*my_strjoin(char const *s1, char const *s2);

//Environment
void	copy_environment(t_env *env, char **envp);
int		check_builtins(t_parser *cmd, t_env *env);
void	change_variable(t_env *env, char *key, char *new_value);
void	print_env(t_env *env);

//cd
void	change_directory(t_parser *cmd, t_env *env);

//BUILTINS
//export
void	print_export(t_env *env);
void	add_to_env(t_env *env, char *new_val);
int		check_export(t_parser *cmd, t_env *env);
int		is_valid_argument(char *arg);
int		exists_in_env(t_env *env, char *var);
char	*get_var_name(char *var);
void	update_env(t_env *env, char *var);

# endif