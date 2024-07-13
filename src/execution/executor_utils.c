/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:48:35 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/13 17:09:47 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_parser(t_parser *head)
{
	t_parser	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_free(tmp->args);
		ft_free(tmp);
	}
}

void	ft_free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i])
	{
		ft_free(split[i]);
		i++;
	}
	ft_free(split);
}

char	*my_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (*s1)
	{
		result[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		result[i++] = *s2;
		s2++;
	}
	result[i++] = '\0';
	return (result);
}
