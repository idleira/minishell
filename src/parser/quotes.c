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

//takes a string and removes any quotation marks, then saves the modified string
void	quotes_strip(t_parser *parser, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			parser->quote = s[i];
			++i;
			while (s[i] != parser->quote && s[i])
			{
				parser->line = ft_strjoin(parser->line, ft_substr(s, i, 1));
				++i;
			}
		}
		else
			parser->line = ft_strjoin(parser->line, ft_substr(s, i, 1));
		++i;
	}
	parser->line = ft_strjoin(parser->line, ft_strdup("\n"));
}

//takes an array of strings, removes quotes from each, and splits them into separate strings
void	quotes_process(t_parser *parser)
{
	parser->line = NULL;
	parser->i = -1;
	while (parser->tokens[++parser->i])
		quotes_strip(parser, parser->tokens[parser->i]);
	parser->tokens2 = ft_split(parser->line, '\n');
}
