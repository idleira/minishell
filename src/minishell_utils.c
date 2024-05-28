/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers_free.c                                    :+:      :+:    :+:   */
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

// frees all pointers
void	ptrs_free(t_prompt *prompt, t_scanner *scanner,
	t_errors *error)
{
	free(prompt->line);
	free(prompt);
	free(scanner->command);
	scanner_free(scanner->tokens);
	free(scanner);
	free(error);
}

// checks if the command is empty
int	ft_check(t_scanner *scanner, t_prompt *prompt, t_errors *error)
{
	// (void)error;
	if (!scanner->command)
	{
		free(prompt);
		free(scanner);
		return (1);
	}
	if (check_spaces(scanner->command))
	{
		free(prompt->line);
		free(prompt);
		free(scanner->command);
		free(scanner);
		free(error);
		return (2);
	}
	return (0);
}

//handles parsing errors in the command
void	input_process(t_scanner *scanner, t_dlist *head, t_errors *error,
	t_prompt *prompt)
{
	t_parser	*parser;

	parser = NULL;
	(void)prompt;
	ft_scanner(scanner);
	ft_lexer(&head, scanner);
	ft_error(head, error);
	if (error->error_type != no_error)
	{
		error_display(error);
		node_free(head, 0);
	}
	else
	{
		quotes_remove(head);
		parse_cmd_list(&parser, head);
		traverse_parser(parser);
		// node_free(head, 1);
	}
	add_history(scanner->command);
	// ptrs_free(prompt, scanner, error);
}
