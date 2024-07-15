/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:03:16 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/07/15 15:10:29 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expander_check(t_parser *cmd, t_env *env)
{
	
	if (cmd->args[i][0] == '$' && cmd->args[i][1] == '\0')
				printf("$");
			if (cmd->args[i][0] == '$' && cmd->q_single == false)
			{
				var_name = cmd->args[i] + 1;
				var_value = get_var_value(env, var_name);
				if (var_value)
					printf("%s", var_value);
			}
			else
}