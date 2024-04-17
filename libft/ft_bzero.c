/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:44:01 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 12:47:35 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* set a block of memory to zero */
void	ft_bzero(void *s, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < len)
	{
		ptr[i] = 0;
		i++;
	}
}

// int main()
// {
//     char str[10] = "bonjour";
//     printf("Before: %s\n", str);
//     ft_bzero(str, strlen(str));
//     printf("After:  %s\n", str);
//     return (0);
// }