/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:12:22 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 13:48:07 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* move block of memory */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_arr;
	unsigned char	*src_arr;
	size_t			i;

	i = 0;
	dst_arr = (unsigned char *)dst;
	src_arr = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (len-- > 0)
			dst_arr[len] = src_arr[len];
	}
	else
	{
		while (i < len)
		{
			dst_arr[i] = src_arr[i];
			i++;
		}
	}
	return (dst);
}

// int main()
// {
// 	char str2[] = "bonjour";
// 	char str1[20];
// 	size_t len = 7;
// 	ft_memmove(str1, str2, len);
// 	printf("Moved string is: %s\n", str2);
// }