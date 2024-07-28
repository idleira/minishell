/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:10:10 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 16:10:10 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// handles quotes in the command
void	handle_quotes(t_scanner *scanner)
{
	char	quote;

	quote = scanner->command[scanner->i];
	scanner->j = scanner->i++;
	while (scanner->command[scanner->i] != quote
		&& scanner->command[scanner->i])
		scanner->i++;
	if (scanner->command[scanner->i])
		scanner->line = ft_strjoin(scanner->line,
				ft_substr(scanner->command, scanner->j,
					scanner->i - scanner->j + 1));
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
	else if (scanner->command[scanner->i] == '|')
	{
		scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
		scanner->line = ft_strjoin(scanner->line,
				ft_substr(scanner->command, scanner->i, 1));
		scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
	}
	else
	{
		scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
		scanner->line = ft_strjoin(scanner->line,
				ft_substr(scanner->command, scanner->i, 1));
		scanner->line = ft_strjoin(scanner->line, ft_strdup("\n"));
	}
}

// ft_frees scanner resources
void	scanner_ft_free(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		ft_free(tokens[i]);
	ft_free(tokens);
}
