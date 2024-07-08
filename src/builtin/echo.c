/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:42:38 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/06/27 15:52:39 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_echo(t_parser *cmd, t_env *env)
{
	char	*var_name;
	char	*var_value;
	bool	is_newline;
	int		i;

	is_newline = true;
	i = 1;
	if (cmd->args[i] && strcmp(cmd->args[i], "-n") == 0)
	{
		is_newline = false;
		i++;
	}
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '$')
		{
			var_name = cmd->args[i] + 1;
			var_value = get_var_value(env, var_name);
			if (var_value)
				printf("%s", var_value);
		}
		else
			printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (is_newline)
		printf("\n");
	return (1);
}