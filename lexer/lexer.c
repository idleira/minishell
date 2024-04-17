/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:04:11 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/17 17:12:35 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "lexer.h"

//allocate memory for new token, copy the content, init other fields (index, type)
t_word	*token_new(char *content, int index, t_word_type type)
{
	t_word	*token;
	
	token = (t_word *)malloc(sizeof(t_word));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	if (!token->content)
	{
		free(token);
		return (NULL);
	}
	token->index = index;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

//create new token, add it to the list and update the first and last pointers
t_word	*token_create(t_split *tokens, char *start, int index, t_word_type type)
{
	t_word	*token;

	token = token_new(start, index, type);
	if (!token)
	{
		free(tokens);
		return (NULL);
	}
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
	t_split	*tokens;
	
	tokens->cmds = 0;
	tokens->first = NULL;
	tokens->last = NULL;
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

//tokenize the input string: iterate over the string and call token_handle when encoutering a space or an operator
t_split	*tokenize(char *s)
{
	t_info	info;
	t_split	*tokens;
	char	*start;
	int		i;

	tokens = (t_split *)malloc(sizeof(t_split));
	if (!tokens)
		return (NULL);
	i = 0;
	start = s;
	token_info_init(&info, &start, s, &i);
	while (s[i])
	{
		if (is_space(s[i]) || s[i] == '|' || s[i] == '<' || s[i] == '>')
		{
			token_handle(tokens, &info, CMD);
			token_handle(tokens, &info, OPERATOR);
		}
		i++;
	}
	if (start != &s[i])
		token_create(tokens, start, i, CMD);
	return (tokens);
}

// int main()
// {
// 	t_word *token = token_new("test", 1, WORD);
//     if (token == NULL)
// 	{
//         printf("Failed to create token\n");
//         return (1);
//     }
//     if (strcmp(token->content, "test") != 0)
// 	{
//         printf("Content is not set correctly\n");
//         return (1);
//     }
//     if (token->index != 1)
// 	{
//         printf("Index is not set correctly\n");
//         return (1);
//     }
//     if (token->type != WORD)
// 	{
//         printf("Type is not set correctly\n");
//         return (1);
//     }
//     if (token->next != NULL)
// 	{
//         printf("Next is not set correctly\n");
//         return (1);
//     }
//     if (token->prev != NULL)
// 	{
//         printf("Prev is not set correctly\n");
//         return (1);
//     }
//     printf("token_new passed all tests\n");
//     t_split *tokens = (t_split *)malloc(sizeof(t_split));
//     t_word *token2 = token_create(tokens, "test2", 2, WORD);
//     if (token2 == NULL) {
//         printf("Failed to create token\n");
//         return (1);
//     }
//     printf("token_create passed all tests\n");
//     return (0);
// }