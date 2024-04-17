/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:08:47 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 13:31:30 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* compare two blocks of memory */
int	ft_memcmp(const void *s1, const void *s2, size_t len)
{
	size_t				i;
	unsigned char		*s_1;
	unsigned char		*s_2;

	i = 0;
	s_1 = (unsigned char *)s1;
	s_2 = (unsigned char *)s2;
	while (i < len)
	{
		if (s_1[i] != s_2[i])
			return (s_1[i] - s_2[i]);
		i++;
	}
	return (0);
}

// int main()
// {
// 	char str1[] = "A noisy noise annoys";
// 	char str2[] = "A noisy noise annoys an oyster most.";
// 	size_t len1 = 20;
// 	int  result1 = ft_memcmp(str1, str2, len1);
// 	printf("Result = %d\n", result1);
// }