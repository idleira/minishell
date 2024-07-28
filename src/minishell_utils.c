/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers_ft_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:02:21 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 16:02:21 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//handles parsing errors in the command
int	input_process(t_shell *minishell)
{
	ft_scanner(minishell);
	ft_lexer(minishell);
	ft_error(minishell);
	if (minishell->error->error_type != no_error)
	{
		error_display(minishell->error);
		node_ft_free(minishell->lexer);
		add_history(minishell->scanner->command);
		return (1);
	}
	else
		parse_cmd_list(&minishell->parser, minishell->lexer);
	add_history(minishell->scanner->command);
	return (0);
}

void	process_and_execute(t_shell *minishell)
{
	minishell->scanner = (t_scanner *)ft_malloc(sizeof(t_scanner));
	minishell->error = (t_errors *)ft_malloc(sizeof(t_errors));
	minishell->parser = (t_parser *)ft_malloc(sizeof(t_parser));
	minishell->scanner->command = input_get(minishell->prompt);
	minishell->lexer = NULL;
	minishell->parser = NULL;
	if (ft_check(minishell->scanner, minishell->prompt, minishell->error) == 1)
		minishell_exit(1, false);
	if (ft_check(minishell->scanner, minishell->prompt, minishell->error) != 2)
	{
		if (input_process(minishell) == 0 && minishell->parser->args[0])
		{
			free(minishell->scanner->command);
			chose_execution(minishell->parser);
		}
		ft_free_parser(minishell->parser);
	}
	ft_free(minishell->scanner);
	ft_free(minishell->error);
}
