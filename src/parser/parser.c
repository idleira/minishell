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
void	parse(t_parser **parser, t_dlist *head)
{
	t_parser		*node;
	t_list			*file;
	char			*args;

	while (head)
	{
		node = node_create_parser();
		node->file = NULL;
		file = NULL;
		args = NULL;
		while (head && head->type != __PIPE)
		{
			if ((head->type == __WORD && !head->prev)
				|| (head->type == __WORD && (head->prev->type == __WORD
						|| head->prev->type == __PIPE)))
			{
				args = ft_strjoin(args, head->value);
				args = ft_strjoin(args, ft_strdup("\n"));
			}
			else if ((head->type == __RED_APP || head->type == __RED_IN
					|| head->type == __HEREDOC || head->type == __RED_OUT))
			{
				file = ft_lstnew();
				file->name = head->next->value;
				if (head->type == __RED_IN)
					file->type = IN;
				else if (head->type == __RED_OUT)
					file->type = OUT;
				else if (head->type == __RED_APP)
					file->type = APPEND;
				else if (head->type == __HEREDOC)
					file->type = HEREDOC;
				else
					file->type = NONE;
				ft_lstadd_back(&node->file, file);
			}
			head = head->next;
		}
		if (args)
			node->args = ft_split(args, '\n');
		else
			node->args = NULL;
		node_append_parser(parser, node);
		if (head)
			head = head->next;
	}
}
