/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:02:12 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/24 20:45:45 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* copy block of memory */
void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst_arr;
	unsigned char	*src_arr;

	i = 0;
	dst_arr = (unsigned char *)dst;
	src_arr = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < len)
	{
		dst_arr[i] = src_arr[i];
		i++;
	}
	return (dst);
}

// int main()
// {
// 	char str2[] = "bonjour";
// 	char str1[20];
// 	size_t len = 7;
// 	ft_memcpy(str1, str2, len * sizeof(char));
// 	printf("Copied string is: %s\n", str2);
// }