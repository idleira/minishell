/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:43:07 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/27 17:43:07 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// parses the lexer list and creates a parser list
void	parser(t_parser *parser, t_dlist *head)
{
	t_parser		*node;
	char			*args;
	int				i;

	(void)parser;
	while (head)
	{
		i = 0;
		node = node_create_parser();
		args = NULL;
		while (head && head->type != __PIPE)
		{
			if ((head->type == __WORD && !head->prev)
				|| (head->type == __WORD && (head->prev->type == __WORD
						|| head->prev->type == __PIPE)))
				printf("%s\n", head->value);
			head = head->next;
		}
		if (head)
			head = head->next;
	}
}
