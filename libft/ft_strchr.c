/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:44:38 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/24 16:29:07 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* locate first occurrence of character in string */
char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	target;

	i = 0;
	target = (unsigned char)c;
	while (str[i])
	{
		if (str[i] == target)
			return ((char *)str + i);
		i++;
	}
	if (target == '\0')
		return ((char *)str + i);
	return (0);
}

// int main()
// {
//     const char *str = "A noisy noise annoys an oyster most.";
//     int target = 'y';
//     char *result = ft_strchr(str, target);
//     if (result != NULL)
//         printf("'%c' is found at position: %ld\n", target, result - str);
//     else
//         printf("'%c' was not found in the string.\n", target);
//     return 0;
// }
// //
//assigning unsigned char to c allows for proper comparison
//even if c is outside the range of char value