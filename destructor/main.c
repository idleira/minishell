/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:47:07 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/08 14:52:48 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_alloc.h"

// int	main(void)
// {
// 	// init list for allocations
// 	ft_alloc_init();

// 	// allocations with ft_ft_malloc
// 	char *str = ft_ft_malloc(455 * sizeof(char));
// 	char *str2 = ft_ft_malloc(455 * sizeof(char));
// 	char *str3 = ft_ft_malloc(455 * sizeof(char));

// 	// manual ft_free
// 	ft_ft_free(str);  
// 	ft_ft_free(str2);
// 	ft_ft_free(str3);

// 	int i = 0;
// 	while (i < 10)
// 	{
// 		// allocation without ft_ft_free
// 		char *str4 = ft_ft_malloc(455 * sizeof(char));
// 		(void)str4;
// 		i++;
// 	}

// 	// original ft_malloc - won't be ft_freed with destructor
// 	char *str5 = ft_malloc(455 * sizeof(char)); 
// 	(void)str5;

// 	// will ft_free everything that was allocated with ft_ft_malloc or ft_calloc
// 	ft_destructor();
// 	return (0);
// }