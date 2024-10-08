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

// splits the command into tokens
void	cmds_split(t_scanner *scanner)
{
	while (scanner->command[scanner->i])
	{
		if (scanner->command[scanner->i] == '\"'
			|| scanner->command[scanner->i] == '\'')
			handle_quotes(scanner);
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

int	quote_check(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (quote == '\0')
				quote = str[i];
			else if (quote == str[i])
				quote = '\0';
		}
		i++;
	}
	if (quote != '\0')
		return (1);
	return (0);
}

// initializes the scanner struct, splits and tokenizes input commands
void	ft_scanner(t_shell *minishell)
{
	t_scanner	*scanner;

	scanner = minishell->scanner;
	if (quote_check(scanner->command) == 1)
	{
		printf("bash: syntax error: unclosed quotes\n");
		exit(2);
	}
	scanner->i = 0;
	scanner->line = NULL;
	cmds_split(scanner);
	scanner->tokens = ft_split(scanner->line, '\n');
	ft_free(scanner->line);
	ft_expander(scanner->tokens);
}
