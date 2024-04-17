/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:02:09 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 15:30:17 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* extract substring from given string */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	input_len;

	if (!s)
		return (NULL);
	input_len = ft_strlen(s);
	if (start >= input_len)
		return (ft_strdup(""));
	if (len > input_len - start)
		return (ft_strdup(s + start));
	sub = malloc ((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	ft_strlcpy (sub, start + s, len + 1);
	return (sub);
}
