/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:52:01 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 14:22:09 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* create duplicate of string */
char	*ft_strdup(const char *str)
{
	int		i;
	char	*dup;
	int		strlen;

	i = 0;
	strlen = ft_strlen (str);
	dup = malloc(sizeof(char) * (strlen + 1));
	if (!dup)
		return (NULL);
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

// int main()
// {
//     const char *str = "bonjour";
//     char *duplicate = ft_strdup(str);
//     if (duplicate != NULL)
//     {
//         printf("Original string: %s\n", str);
//         printf("Duplicated string: %s\n", duplicate);
//         free(duplicate); 
//     }
//     return (0);
// }
