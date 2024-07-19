/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers_ft_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:02:21 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 16:02:21 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// checks if the string is only spaces and tabs
int	check_spaces(char *s)
{
	while (*s && (*s == '\t' || *s == ' '))
		++s;
	if (*s)
		return (0);
	return (1);
}

// ft_frees all pointers
void	ptrs_ft_free(t_prompt *prompt, t_scanner *scanner,
	t_errors *error)
{
	ft_free(prompt->line);
	ft_free(prompt);
	ft_free(scanner->command);
	scanner_ft_free(scanner->tokens);
	ft_free(scanner);
	ft_free(error);
}

// checks if the command is empty
int	ft_check(t_scanner *scanner, t_prompt *prompt, t_errors *error)
{
	// (void)error;
	if (!scanner->command)
	{
		ft_free(prompt);
		ft_free(scanner);
		return (1);
	}
	if (check_spaces(scanner->command))
	{
		// ft_free(prompt->line);
		// ft_free(prompt);
		// ft_free(scanner->command);
		// // ft_free(scanner);
		// // ft_free(error);
		(void)error;
		return (2);
	}
	return (0);
}

//handles parsing errors in the command
t_parser	*input_process(t_scanner *scanner, t_dlist *head, t_errors *error,
	t_prompt *prompt)
{
	t_parser	*parser;

	parser = NULL;
	(void)prompt;
	ft_scanner(scanner);						// scan user's input command and store it in scanner->tokens
	ft_lexer(&head, scanner);					// convert the scanned input into a doubly linked list of tokens
	ft_error(head, error);						// check for errors in the tokenized input
	if (error->error_type != no_error)
	{
		error_display(error);
		node_ft_free(head, 0);
	}
	else										// if no errors, parse the command										
	{
		quotes_remove(head);					// remove quotes from the tokens
		parse_cmd_list(&parser, head);			// parse the tokens and create a parser node for each cmd separated by a pipe
		//traverse_parser(parser);				// prints out arguments and files associated with each parser node
		// node_ft_free(head, 1);
	}
	add_history(scanner->command);				// add the command to the history
	// ptrs_ft_free(prompt, scanner, error);
	return (parser);
}
