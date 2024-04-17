/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:31:43 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 13:59:00 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* fill block of memory */
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	val;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)b;
	val = (unsigned char)c;
	while (i < len)
	{
		ptr[i] = val;
		i++;
	}
	return (b);
}

// int main()
// {
// 	char str[7] = "bonjour";
// 	ft_memset(str, '!' , 4);
// 	printf("Modified string: %s\n", str);
// }