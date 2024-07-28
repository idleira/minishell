/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:59:43 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/07/26 13:06:18 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// checks if the string is only spaces and tabs
int	check_spaces(char *s)
{
	while (*s && (*s == '\t' || *s == ' '))
		++s;
	if (*s)
		return (0);
	return (1);
}

// ft_frees all pointers
void	ptrs_ft_free(t_prompt *prompt, t_scanner *scanner,
	t_errors *error)
{
	ft_free(prompt->line);
	ft_free(prompt);
	ft_free(scanner->command);
	scanner_ft_free(scanner->tokens);
	ft_free(scanner);
	ft_free(error);
}

// checks if the command is empty
int	ft_check(t_scanner *scanner, t_prompt *prompt, t_errors *error)
{
	if (!scanner->command)
	{
		ft_free(prompt);
		ft_free(scanner);
		return (1);
	}
	if (check_spaces(scanner->command))
	{
		(void)error;
		return (2);
	}
	return (0);
}
