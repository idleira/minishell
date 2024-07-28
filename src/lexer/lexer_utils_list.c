/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:42:01 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/27 17:42:01 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// creates a new node for the lexer list
t_dlist	*node_create_lex(void)
{
	t_dlist	*new;

	new = (t_dlist *)ft_malloc(sizeof(t_dlist));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

// returns the last node of the lexer list
t_dlist	*node_last_lex(t_dlist *head)
{
	t_dlist	*temp;

	temp = head;
	if (!temp)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}

// appends a new node to the lexer list
void	node_append_lex(t_dlist **head, t_dlist *new)
{
	t_dlist	*temp;

	temp = node_last_lex(*head);
	if (temp)
	{
		temp->next = new;
		new->prev = temp;
		return ;
	}
	*head = new;
}

// prints the doubly linked lexer list
void	traverse_list(t_dlist *head)
{
	t_dlist	*temp;

	temp = head;
	if (!temp)
		return ;
	while (temp)
	{
		printf("\nvalue ---> %s\n", temp->value);
		printf("type  ---> %d\n", temp->type);
		temp = temp->next;
	}
}

// ft_frees the doubly linked lexer list
void	node_ft_free(t_dlist *head)
{
	t_dlist	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		ft_free(temp);
	}
}
