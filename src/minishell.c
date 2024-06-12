/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:12:37 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 15:12:37 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_scanner	*scanner;
	t_prompt	*prompt;
	t_dlist		*head;
	t_errors	*error;
	int			return_value;
	t_parser	*parsed_commands;
	t_env		*env;
	

	(void)argc;
	(void)argv;
	env = (t_env *)malloc(sizeof(t_env));
	copy_environment(env, envp);
	while (1)
	{
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		scanner = (t_scanner *)malloc(sizeof(t_scanner));
		error = (t_errors *)malloc(sizeof(t_errors));
		scanner->command = input_get(prompt);									// get user's input command and store it in scanner->command
		if (ft_strncmp(scanner->command, "exit", 5) == 0)
		{
			free(prompt);
			free(scanner);
			free(error);
			exit(0);
		}
		head = NULL;
		return_value = ft_check(scanner, prompt, error);
		if (return_value == 1)
			exit(1);
		if (return_value != 2)
		{
			parsed_commands = input_process(scanner, head, error, prompt);		// parse the command and store it in t_parser struct
			if (parsed_commands)
				chose_execution(parsed_commands, envp);
			free_parser(parsed_commands);
		}
		free(prompt);
		free(scanner);
		free(error);
	}
	return (0);
}
