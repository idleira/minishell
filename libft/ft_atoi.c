/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:03:01 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/05/23 12:40:16 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* convert str representation of int to int value */
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign *= -1;
	while (*str == '-' || *str == '+')
	{
		str++;
		i++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if (i > 1)
		return (0);
	return (result * sign);
}

// int main()
// {
//     const char *str = "-42"; 
//     int result = ft_atoi(str);
//     printf("Result: %d\n", result);
//     return (0);
// }

// if current result is 23 and current digit is '5' :
// 1. result * 10 : 23 * 10 = 230 (make room for next digit)
// 2. + *str : 230 + '5' = 230 + 5 = 235 (add current digit character to result)
// 3. - '0' : 235 - 48 = 235 (subtract ascii value of '0' to convert character
// 								to digit of it's corresponding numeric value)