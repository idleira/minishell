/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:15:34 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/15 17:58:45 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

t_word *new_token(char *content, int index, t_word_type type)
{
	t_word *token;

	token = (t_word *)malloc(sizeof(t_word));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	token->index = index;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_word *create_token(t_split *tokens, char *start, int i, t_word_type type)
{
	t_word *token = new_token(start, i, type);
	if (tokens->last)
	{
		tokens->last->next = token;
		token->prev = tokens->last;
		tokens->last = token;
	}
	else
	{
		tokens->first = token;
		tokens->last = token;
	}
	return token;
}

void handle_token(t_split *tokens, char **start, char *s, int *i, t_word_type type)
{
	if (*start != &s[*i])
	{
		if (type == CMD)
			create_token(tokens, *start, *i, CMD);
		else
			create_token(tokens, *start, *i, OPERATOR);
	}
	create_token(tokens, &s[*i], *i, type);
	*start = &s[*i + 1];
}

t_split *tokenize(char *s)
{
	t_split *tokens;
	char *start;
	int i;

	tokens = (t_split *)malloc(sizeof(t_split));
	if (!tokens)
		return (NULL);
	tokens->cmds = 0;
	tokens->first = NULL;
	tokens->last = NULL;
	start = s;
	i = 0;
	while (s[i])
	{
		if (is_space(s[i]) || s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			handle_token(tokens, &start, s, &i, CMD);
			handle_token(tokens, &start, s, &i, OPERATOR);
		}
		i++;
	}
	if (start != &s[i])
		create_token(tokens, start, i, CMD);
	return (tokens);
}
