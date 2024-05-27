/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:44:35 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/27 17:44:35 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// counts the number of file redirections in the parser list
int	count_file_red(t_dlist	*head)
{
	t_dlist	*temp;
	int		number;

	temp = head;
	number = 0;
	while (temp && temp->type != __PIPE)
	{
		if (temp->type == __RED_IN || temp->type == __RED_OUT
			|| temp->type == __RED_APP || temp->type == __HEREDOC)
			++number;
		temp = temp->next;
	}
	return (number);
}

// counts the number of arguments in the parser list
int	count_args(t_dlist *head)
{
	t_dlist	*temp;
	int		number;

	temp = head;
	number = 0;
	while (temp && temp->type != __PIPE)
	{
		if ((temp->type == __WORD && !temp->prev)
			|| (temp->type == __WORD && temp->prev->type == __WORD))
			++number;
		temp = temp->next;
	}
	return (number);
}

// assigns the file redirections to the parser struct
void	assign_file_red(t_dlist *head, t_parser *node, int i)
{
	node->file[i].type = head->type;
	node->file[i].name = ft_strdup(head->next->value);
}

void	assign_args(t_dlist *head, t_parser *node, char *args)
{
	(void)head;
	node->args = ft_split(args, '\n');
}
