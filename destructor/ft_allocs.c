/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:30:23 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/27 15:31:12 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc.h"

void	*ft_malloc(size_t size)
{
	t_allocs	*allocs;
	void		*ptr;

	allocs = ft_allocs(NULL);
	if (allocs == NULL)
		return (malloc(size));
	ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("Memory allocation failed\n");
		ft_destructor();
		exit(EXIT_FAILURE);
	}
	if (FT_DESTR)
		add_allocnode(&allocs, create_alloc(ptr));
	return (ptr);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_allocs	*allocs;
	void		*new_ptr;

	if (ptr == NULL)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	allocs = ft_allocs(NULL);
	if (allocs == NULL)
		return (realloc(ptr, size));
	new_ptr = ft_malloc(size);
	if (new_ptr == NULL)
		return (NULL);
	my_memcpy(new_ptr, ptr, size);
	ft_free(ptr);
	return (new_ptr);
}

void	*my_memcpy(void *dst, const void *src, size_t len)
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
