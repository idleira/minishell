/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:25:28 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 13:09:39 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* number of digits in int */
static int	count(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/* convert int to str */
static char	*convert(int len, int p, char *ptr, int n)
{
	while (len + 1 > p)
	{
		if (n < 0)
			ptr[len] = n % 10 * (-1) + '0';
		else
			ptr[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (ptr);
}

/* convert integer to string */
char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		position;

	len = 0;
	len = count(n);
	ptr = (char *) malloc (len + 1);
	if (!ptr)
		return (NULL);
	position = 0;
	if (n < 0)
	{
		ptr[0] = '-';
		position = 1;
	}
	ptr[len] = '\0';
	len--;
	return (convert(len, position, ptr, n));
}
