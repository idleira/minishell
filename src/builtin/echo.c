/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:42:38 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/15 14:58:35 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_echo(t_parser *cmd, t_env *env)
{
	bool	is_newline;
	int		i;

	is_newline = true;
	i = 1;
	if (cmd->file)
		return (0);
		if (cmd->args[0] && (ft_strncmp(cmd->args[0], "echo", 5) == 0 || ft_strncmp(cmd->args[0], "echo ", 6) == 0))
		{
			if (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
			{
				is_newline = false;
				i++;
			}
		print_echo(cmd, env, i);
		if (is_newline)
			printf("\n");
		return (1);
		}
		else
		{
			printf("%s: command not found\n", cmd->args[0]);
			return (0);
		}
}

void	print_echo(t_parser *cmd, t_env *env, int i)
{
	char	*var_name;
	char	*var_value;

	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '$' && cmd->q_single == false && cmd->args[i][1] != '\0')
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
}
