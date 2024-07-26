/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:04:11 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/18 18:23:40 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// tokenizes the input string and creates nodes for the lexer list
void	tokenizer(t_dlist **head, char *token)
{
	if (token[0] == '\'' || token[0] == '\"')
		node_append_lex(head, node_quotes(token));
	else if (!strcmp(token, ">") || !strcmp(token, "<")
		|| !strcmp(token, ">>") || !strcmp(token, "<<"))
		node_append_lex(head, node_redirection(token));
	else if (!strcmp(token, "|"))
		node_append_lex(head, node_pipeline(token));
	else
		node_append_lex(head, node_word(token));
}

// processes the input string and tokenizes it
void	ft_lexer(t_shell *minishell)
{
	t_scanner	*scanner;

	scanner = minishell->scanner;
	scanner->i = 0;
	while (scanner->tokens[scanner->i])
	{
		tokenizer(&minishell->lexer, scanner->tokens[scanner->i]);
		++scanner->i;
	}
}
