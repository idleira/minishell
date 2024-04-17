/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:02:58 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 16:05:28 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* search for last occurrence of character in string */
char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			ptr = (char *)(str + i);
		i ++;
	}
	if (str[i] == (char)c)
		ptr = (char *)(str + i);
	return (ptr);
}

// int main()
// {
//     const char *str = "A noisy noise annoys an oyster most.";
//     int trg = 'n';
//     char *result = ft_strrchr(str, trg);
//     if (result != NULL)
//     {
//         printf("Last '%c' is found at position: %ld\n", trg, result - str);
//         printf("Substring: %s\n", result);
//     }
//     else
//     {
//         printf("Character '%c' not found in the string\n", trg);
//     }
//     return (0);
// }
