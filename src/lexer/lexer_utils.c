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
t_dlist	*node_quotes(char *token)
{
	t_dlist	*node;

	node = node_create_lex();
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
	node->type = __PIPE;
	return (node);
}

// creates a lexer node for a word token
t_dlist	*node_word(char *token)
{
	t_dlist	*node;

	node = node_create_lex();
	node->value = token;
	node->type = __WORD;
	return (node);
}