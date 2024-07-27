/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:42:38 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/27 21:22:39 by mzhukova         ###   ########.fr       */
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
	if (cmd->args[0] && (ft_strncmp(cmd->args[0], "echo", 5) == 0
			|| ft_strncmp(cmd->args[0], "echo ", 6) == 0))
	{
		while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
		{
			if (cmd->args[i][2] != '\0' && not_only_n(cmd->args[i]) != 0)
				break ;
			is_newline = false;
			i++;
		}
		print_echo(cmd, i);
		if (is_newline)
			printf("\n");
		return (1);
	}
	return (0);
}

void	print_echo(t_parser *cmd, int i)
{
	while (cmd->args[i])
	{
		if (ft_strncmp(cmd->args[i], "$?", 2) == 0)
			printf("%d", g_env->exit_status);
		else
		{
			printf("%s", cmd->args[i]);
		}
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

void	print_error(t_parser *cmd, char *cmd_w_path)
{
	printf("command not found: %s\n", cmd_w_path);
	_exit(127);
}
