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

int	check_spaces_tabs(char *s)
{
	while (*s && (*s == '\t' || *s == ' '))
		++s;
	if (*s)
		return (0);
	return (1);
}

void	pointers_free(t_prompt *prompt, t_scanner *scanner,
	t_errors *error)
{
	free(prompt->line);
	free(prompt);
	free(scanner->command);
	scan_free(scanner->tokens);
	free(scanner);
	free(error);
}

int	check_cmd_empty(t_scanner *scanner, t_prompt *prompt)
{
	if (!scanner->command)
	{
		free(prompt);
		free(scanner);
		return (1);
	}
	if (check_spaces_tabs(scanner->command))
	{
		free(prompt->line);
		free(prompt);
		free(scanner->command);
		free(scanner);
		return (2);
	}
	return (0);
}

void	error_parse_handle(t_scanner *scanner, t_dlist *head, t_errors *error,
	t_prompt *prompt)
{
	t_parser	*parser;

	parser = NULL;
	scanner(scanner);
	lexer(&head, scanner);
	error_handle(head, error);
	if (error->error_type != no_error)
	{
		error_display(error);
		node_free(head, 0);
	}
	else
	{
		quotes_remove(head);
		parser(parser, head);
		node_free(head, 1);
	}
	add_history(scanner->command);
	pointers_free(prompt, scanner, error);
}

