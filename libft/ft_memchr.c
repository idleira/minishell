/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:59:34 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 13:18:20 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* locate character in block of memory */
void	*ft_memchr(const void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	uc;

	i = 0;
	ptr = (unsigned char *)str;
	uc = (unsigned char)c;
	while (i < len)
	{
		if (ptr[i] == uc)
			return (ptr + i);
		i++;
	}
	return (NULL);
}

// int main()
// {
//     char array[60] = "A noisy noise annoys an oyster most.";
//     int c = 'i';
//     char *ptr;
//     unsigned long size = 10;
//     ptr = ft_memchr(array, c, size);
//     if (ptr != NULL)
//         printf("Character '%c' is in position %ld\n", *ptr, (ptr - array));
//     else
//         printf("Character not found.\n");
//     return (0);
// }
//
//treating memory block as an array of unsigned chars, allows for comparison
//of individual bytes regardless of original type of the memory block
