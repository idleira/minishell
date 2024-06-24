/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:26:25 by mzhukova          #+#    #+#             */
/*   Updated: 2024/06/24 18:45:31 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void print_export(t_env *env)
{
	int	i;

	i = 0;
	while (env->all_vars[i] != NULL)
	{
		printf("declare -x ");
		printf("%s\n", env->all_vars[i]);
		i++;
	}
	//maybe add check for "="
	// if no "=", just print without declare
}