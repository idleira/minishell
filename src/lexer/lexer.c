/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:04:11 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/18 17:56:24 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"

//allocate memory for new token, copy the content, init other fields (index, type)
t_word	*token_new(char *content, int start, int end, t_word_type type)
{
    t_word	*token;
    
    token = (t_word *)malloc(sizeof(t_word));
    if (!token)
        return (NULL);
    token->content = ft_substr(content, start, end - start);
    if (!token->content)
    {
        free(token);
        return (NULL);
    }
    token->index = start;
    token->type = type;
    token->next = NULL;
    token->prev = NULL;
    return (token);
}

//create new token, add it to the list and update the first and last pointers
t_word	*token_create(t_split *tokens, char *start, int index, t_word_type type)
{
    t_word	*token;

    token = token_new(start, index, index + strlen(start), type);
    if (!token)
        return (NULL);
    if (!tokens->head)
    {
        tokens->head = token;
        tokens->tail = token;
    }
    else
    {
        token->prev = tokens->tail;
        tokens->tail->next = token;
        tokens->tail = token;
    }
    return (token);
}
//init the info struct with pointers to the start of the string, the string itself and the current index
void	token_info_init(t_info *info, char **start, char *s, int *i)
{
	info->start = start;
	info->s = s;
	info->i = i;
}

//determine the type of the token and create it
void	token_handle(t_split *tokens, t_info *info, t_word_type type)
{
	if (*(info->start) != &(info->s)[*(info->i)])
		token_create(tokens, *(info->start), *(info->i), type);
	else
		token_create(tokens, &(info->s)[*(info->i)], *(info->i), type);
	*(info->start) = &(info->s)[*(info->i) + 1];
}

//tokenize the input string: split it into tokens, determine their type and create them
t_split	*tokenize(char *s)
{
	t_info	info;
	t_split	*tokens;
	char	*start;
	int		i;

	tokens = (t_split *)ft_calloc(1, sizeof(t_split));
	if (!tokens)
		return (NULL);
	i = 0;
	start = s;
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->cmds = 0;
	tokens->first = NULL;
	tokens->last = NULL;
	token_info_init(&info, &start, s, &i);
	while (s[i])
	{
		if (is_space(s[i]))
		{
			token_handle(tokens, &info, ARG);
			while (s[i] && is_space(s[i]))
				i++;
			start = &s[i];
		}
		else if (s[i] == '|')
		{
			token_handle(tokens, &info, PIPE);
			i++;
			start = &s[i];
		}
		else if (s[i] == '>' || s[i] == '<')
		{
			token_handle(tokens, &info, OPER);
			i++;
			start = &s[i];
		}
		else if (s[i] == '\"' || s[i] == '\'')
		{
			token_handle(tokens, &info, QUOTE);
			i++;
			start = &s[i];
		}
		else
			i++;
	}
	token_handle(tokens, &info, CMD);
	return (tokens);
}


void	print_tokens(t_split *tokens)
{
	t_split *current_token;

	current_token = tokens;
    while (current_token != NULL)
	{
		printf("value: %s, type: %s\n", current_token->value, current_token->type);
		current_token = current_token->next;
	}
}

void free_tokens(t_split *tokens)
{
    t_split *current_token;
    t_split *next_token;

	current_token = tokens;
	while (current_token != NULL)
	{
		next_token = current_token->next;
		free(current_token->value);
		free(current_token->type);
		free(current_token);
		current_token = next_token;
	}
}

int main()
{
	char *s;
	t_split *tokens;
	
	s = "This is a test string | with a pipe";
	tokens = tokenize(s);
	if (tokens == NULL)
	{
		printf("failed to tokenize string\n");
		return (1);
	}
	print_tokens(tokens);
	free_tokens(tokens);
	return (0);
}
