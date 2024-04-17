/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:16:08 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 14:58:23 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* find substring within string, within specified length */
char	*ft_strnstr(const char *big, const char *smol, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*smol)
		return ((char *)big);
	i = 0;
	while (big[i] && (size_t)i < len)
	{
		if (big[i] == smol[0])
		{
			j = 0;
			while (big[i + j] == smol[j] && i + j < len)
			{
				if (smol[j + 1] == '\0')
					return ((char *)&big[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}

// int main() {
//     const char *big = "A noisy noise annoys an oyster most.";
//     const char *smol = "noise annoys an oyster";
//     size_t len = 30;
//     char *result = ft_strnstr(big, smol, len);
//     if (result != NULL) {
//         printf("Substring found at position: %ld\n", result - big);
//         printf("Substring: %s\n", result);
//     } else {
//         printf("Substring not found\n");
//     }
//     return (0);
// }