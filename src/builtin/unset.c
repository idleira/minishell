/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:07:37 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/01 12:07:39 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void unset_var(t_parser *cmd, t_env *env)
{
	int     i;
	int     j;
	int     len;
	char    **new_all_vars;

	i = 0;
	j = 0;
	len = 0;
	while (env->all_vars[len] != NULL)
		len++;
	while (env->all_vars[i])
	{
		if (ft_strncmp(cmd->args[1], env->all_vars[i], ft_strlen(cmd->args[1])) == 0)
			break ;
		i++;
	}
	if (i == len)
	{
		printf("check before return\n");
		return ;
	}
	printf("check after return\n");
	new_all_vars = (char **)malloc(sizeof(char *) * (len + 1)); // Allocate space for the additional NULL pointer
	if (new_all_vars == NULL)
		return ;
	while (j < len)
	{
		if (j != i)
			new_all_vars[j] = env->all_vars[j];
		printf("check in loop\n");
		j++;
	}
	new_all_vars[j] = NULL; // Terminate the new_all_vars array with a NULL pointer
	free(env->all_vars); // Free the old all_vars array
	env->all_vars = new_all_vars;
	print_export(env);
}
