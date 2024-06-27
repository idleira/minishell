/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:42:38 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/06/27 15:22:05 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_echo(t_parser *cmd, t_env *env)
{
	char *var_name;
	char *var_check;
	char *var_value; 
	if (cmd->args[1][0] == '$')
	{
		var_check = cmd->args[1] + 1;
		if (exists_in_env(env, var_check))
		{
			var_name = get_var_name(var_check);
			var_value = get_var_value(env, var_name);
			if (var_value)
			{
				printf("%s\n", var_value);
				return (1);				
			}
		}
	// if (loop through arguments to find -n)
		//printf all the arguments except -n
		//print \n in the end
	}
	return 0;
}