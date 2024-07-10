/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:18:01 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/19 12:58:56 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* combine 2 strings into single string */
char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*p;

	p = (char *)ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!p)
		return ((void *)0);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		++i;
	}
	while (s2[j])
		p[i++] = s2[j++];
	p[i] = '\0';
	ft_free(s1);
	ft_free(s2);
	return (p);
}
