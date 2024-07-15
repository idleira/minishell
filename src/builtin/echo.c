/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:42:38 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/15 18:36:35 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_echo(t_parser *cmd)
{
	bool	is_newline;
	int		i;

	is_newline = true;
	i = 1;
	if (cmd->file)
		return (0);
	if (cmd->args[0] && (ft_strncmp(cmd->args[0], "echo", 5) == 0 || ft_strncmp(cmd->args[0], "echo ", 6) == 0))
	{
		while ((cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0))
		{
			is_newline = false;
			if (not_only_n(cmd->args[i]))
				break ;
			i++;
		}
		print_echo(cmd, i);
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

void	print_echo(t_parser *cmd, int i)
{
	char	*var_name;
	char	*var_value;

	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '$' && cmd->args[i][1] == '\0')
			printf("$\n");
		if (cmd->args[i][0] == '$' && cmd->q_single == false)
		{
			var_name = cmd->args[i] + 1;
			var_value = get_var_value(var_name);
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

int	not_only_n(char *str)
{
	int	i;

	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}