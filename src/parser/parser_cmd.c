/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:54:18 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/18 16:36:54 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// handles quotes in the command
void	handle_quotes(t_scanner *scanner)
{
	scanner->j = scanner->i++;
	while (scanner->command[scanner->i] != scanner->t_quote
		&& scanner->command[scanner->i])
		scanner->i++;
	if (scanner->command[scanner->i])
		scanner->line = ft_strjoin(scanner->line,
				ft_substr(scanner->command, scanner->j,
					scanner->i - scanner->j + 1));
	else
		scanner->line = ft_strjoin(scanner->line,
				ft_substr(scanner->command, scanner->j,
					scanner->i - scanner->j));
}

// handles operators in the command
void	handle_operators(t_scanner *scanner)
{
	if (!ft_memcmp(scanner->command + scanner->i, ">>", 2)
		|| !ft_memcmp(scanner->command + scanner->i, "<<", 2))
	{
		scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
		scanner->line = ft_strjoin(scanner->line,
				ft_substr(scanner->command, scanner->i, 2));
		scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
		scanner->i++;
	}
	else
	{
		scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
		scanner->line = ft_strjoin(scanner->line,
				ft_substr(scanner->command, scanner->i, 1));
		scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
	}
}

// splits the command into tokens
void	cmds_split(t_scanner *scanner)
{
	while (scanner->command[scanner->i])
	{
		if (scanner->command[scanner->i] == '\"'
			|| scanner->command[scanner->i] == '\'')
		{
			scanner->t_quote = scanner->command[scanner->i];
			handle_quotes(scanner);
		}
		else if (ft_strchr("<>|", scanner->command[scanner->i]))
			handle_operators(scanner);
		else if (ft_strchr(" \t\n\v\f\r", scanner->command[scanner->i]))
			scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
		else
			scanner->line = ft_strjoin(scanner->line,
					ft_substr(scanner->command, scanner->i, 1));
		scanner->i++;
	}
}

// initializes the scanner struct, splits and tokenizes input commands
void	ft_scanner(t_scanner *scanner)
{
	scanner->i = 0;
	scanner->line = NULL;
	cmds_split(scanner);
	scanner->tokens = ft_split(scanner->line, '\n');
	free(scanner->line);
}
