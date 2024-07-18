/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:42:38 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/18 12:06:03 by ibeliaie         ###   ########.fr       */
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
		while (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 2) == 0)
		{
			if (cmd->args[i][2] != '\0' && not_only_n(cmd->args[i]) != 0)
        		break;
			is_newline = false;
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

void print_echo(t_parser *cmd, int i)
{
    char *var_name;
    char *var_value;
    int j;

    while (cmd->args[i])
    {
        if (cmd->args[i][0] == '$' && cmd->args[i][1] != '\0' && cmd->q_single == false)
        {
            j = 1;
            while (cmd->args[i][j] && (ft_isalnum(cmd->args[i][j]) || cmd->args[i][j] == '_'))
                j++;
            var_name = ft_substr(cmd->args[i], 1, j - 1);
            var_value = get_var_value(var_name);
            if (var_value)
                printf("%s", var_value);
            printf("%s", cmd->args[i] + j);
            ft_free(var_name);
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