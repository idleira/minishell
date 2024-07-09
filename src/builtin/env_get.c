/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:17:01 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 16:17:01 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// gets the value of an environment variable (using standart one in parser for now)
// char	*ft_getenv(char *string, t_env *env)
// {
// 	t_env	*traverser;

// 	traverser = env;
// 	while (traverser)
// 	{
// 		if (!strcmp(string, traverser->key))
// 			return (traverser->value);
// 		traverser = traverser->next;
// 	}
// 	return (NULL);
// }
