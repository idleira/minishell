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

char	*env_get(char *string, t_env *env)
{
	t_env	*traverser;

	traverser = env;
	while (traverser)
	{
		if (!ft_strcmp(string, traverser->key))
			return (traverser->value);
		traverser = traverser->next;
	}
	return (NULL);
}