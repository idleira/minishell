/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:32:29 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 15:18:54 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* output char ’c’ to given file descriptor */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

//can be useful in various scenarios where you want to redirect
//or write character-level output to a specific destination
//other than the standard output (console)