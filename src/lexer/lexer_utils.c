/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:05 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/17 16:59:00 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// creates a lexer node for a quoted token
t_dlist	*node_quotes(char *token, char quote)
{
	t_dlist	*node;

	node = node_create_lex();
	if (quote == '\'')
		node->state = __s_quotes;
	else
		node->state = __d_quotes;
	node->value = token;
	node->type = __WORD;
	return (node);
}

// creates a lexer node for a redirection token
t_dlist	*node_redirection(char *token)
{
	t_dlist	*node;

	node = node_create_lex();
	node->value = token;
	node->state = __without_quotes;
	if (!strcmp(token, ">"))
		node->type = __RED_OUT;
	else if (!strcmp(token, ">>"))
		node->type = __RED_APP;
	else if (!strcmp(token, "<"))
		node->type = __RED_IN;
	else if (!strcmp(token, "<<"))
		node->type = __HEREDOC;
	return (node);
}

// creates a lexer node for a pipe token
t_dlist	*node_pipeline(char *token)
{
	t_dlist	*node;

	node = node_create_lex();
	node->value = token;
	node->state = __without_quotes;
	node->type = __PIPE;
	return (node);
}

// creates a lexer node for a word token
t_dlist	*node_word(char *token)
{
	t_dlist	*node;

	node = node_create_lex();
	node->value = token;
	node->state = __without_quotes;
	node->type = __WORD;
	return (node);
}

// strips quotes from token
void	quotes_strip(t_dlist *head, char quote)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (head->value[i])
	{
		if (!(head->value[i] == quote))
			temp = ft_strjoin(temp, ft_substr(head->value, i, 1));
		++i;
	}
	head->value = temp;
}
