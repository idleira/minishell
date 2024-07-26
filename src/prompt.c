/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:52:39 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 15:52:39 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// builds the prompt line
void	prompt_build(t_prompt *prompt)
{
	char	*user;
	char	*cwd;

	user = getenv("USER");
	cwd = getcwd(NULL, PATH_MAX);
	if (cwd == NULL)
		return ;
	if (prompt->line != NULL)
		free(prompt->line);
	prompt->line = ft_strjoin(ft_strdup("\001\033[0;32m\002"), ft_strdup(user));
	prompt->line = ft_strjoin(prompt->line,
			ft_strdup(
				"\001\033[0m\002\001\033[1;37m\002 | \001\033[0m\002\001\033[0;36m\002"));
	prompt->line = ft_strjoin(prompt->line,
			ft_strdup(ft_strrchr(cwd, '/') + 1));
	prompt->line = ft_strjoin(prompt->line, ft_strdup("\001\033[0m\002$ "));
	free(cwd);
}

// gets the input from the user
char	*input_get(t_prompt *prompt)
{
	char	*input;

	if (getenv("USER"))
	{
		if (prompt->rebuild)
		{
			prompt_build(prompt);
			prompt->rebuild = 0;
		}
		input = readline(prompt->line);
	}
	else
		input = readline("\033[0;36mminishell\033[0m]$ ");
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	return (input);
}
