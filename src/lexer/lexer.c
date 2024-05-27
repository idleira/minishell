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
	{
		if (token[0] == '\'')
			node_append_lexer(head, node_quotes(token, '\''));
		else
			node_append_lexer(head, node_quotes(token, '\"'));
	}
	else if (!ft_strcmp(token, ">") || !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">>") || !ft_strcmp(token, "<<"))
		node_append_lexer(head, node_redirection(token));
	else if (!ft_strcmp(token, "|"))
		node_append_lexer(head, node_pipeline(token));
	else
		node_append_lexer(head, node_word(token));
}

// // removes token quotes from lexer
void	quotes_remove(t_dlist *head)
{
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	while (head)
	{
		if (head->state == __s_quotes)
			quotes_strip(head, '\'');
		else if (head->state == __d_quotes)
			quotes_strip(head, '\"');
		head = head->next;
	}
}

// processes the input string and tokenizes it
void	lexer(t_dlist **head, t_scanner *scanner)
{
	scanner->i = 0;
	while (scanner->tokens[scanner->i])
	{
		tokenizer(head, scanner->tokens[scanner->i]);
		++scanner->i;
	}
}
