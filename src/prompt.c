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
	cwd = getcwd(NULL, 0);
	prompt->line = ft_strjoin(ft_strdup("[\033[0;32m"), ft_strdup(user));
	prompt->line = ft_strjoin(prompt->line,
			ft_strdup("\033[0m\033[1;37m | \033[0m\033[0;36m "));
	prompt->line = ft_strjoin(prompt->line,
			ft_strdup(ft_strrchr(cwd, '/') + 1));
	prompt->line = ft_strjoin(prompt->line, ft_strdup("\033[0m]$ "));
	free(cwd);
}

// gets the input from the user
char	*input_get(t_prompt *prompt)
{
    char *input;

    if (getenv("USER"))
    {
        prompt_build(prompt);
        input = readline(prompt->line);
    }
    else
        input = readline("\033[0;36mminishell\033[0m]$ ");
    if (input == NULL)	// if the user presses ctrl+d (readline encountered EOF - end-of-file condition)
    {
		printf("ctrl pressed\n");
        write(1, "exit\n", 5);
        exit(EXIT_SUCCESS);
    }
    return (input);
}
