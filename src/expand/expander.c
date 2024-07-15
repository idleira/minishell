/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:03:16 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/07/15 18:33:19 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expander_check(t_parser *cmd,  )
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