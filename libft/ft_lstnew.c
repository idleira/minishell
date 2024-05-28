/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:41:32 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/20 12:00:32 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* create new node */
t_list	*ft_lstnew(void)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return ((void *)0);
	node->next = (void *)0;
	return (node);
}
