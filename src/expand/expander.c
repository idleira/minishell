/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:03:16 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/07/28 20:58:11 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// check if expansion is needed
static int	is_expansion_needed(char *lexer_token)
{
	int		i;
	bool	expand;

	i = 0;
	expand = false;
	if (!ft_strchr(lexer_token, '$'))
		return (0);
	while (lexer_token[i])
	{
		if (lexer_token[i] == '"')
			expand = !expand;
		if (lexer_token[i] == '\'' && !expand)
		{
			while (lexer_token[++i] != '\'' && lexer_token[i])
				i++;
		}
		if (lexer_token[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

// expand variables when needed
char	**ft_expander(char	**split_tokens)
{
	int		i;
	char	*temp;

	i = 0;
	if (!split_tokens)
		return (NULL);
	while (split_tokens[i])
	{
		if (is_expansion_needed(split_tokens[i]))
		{
			temp = expand_var(split_tokens[i]);
			split_tokens[i] = temp;
		}
		i++;
	}
	return (split_tokens);
}
