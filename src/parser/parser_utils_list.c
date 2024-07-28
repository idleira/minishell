/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:43:49 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/27 17:43:49 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// creates a new node for the parser list
t_parser	*node_create_pars(void)
{
	t_parser	*new;

	new = (t_parser *)ft_malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// returns the last node of the parser list
t_parser	*node_last_pars(t_parser *head)
{
	t_parser	*temp;

	temp = head;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

// appends a new node to the parser list
void	node_append_pars(t_parser **head, t_parser *new)
{
	t_parser	*temp;

	temp = node_last_pars(*head);
	if (temp)
	{
		temp->next = new;
		new->prev = temp;
		return ;
	}
	*head = new;
}
