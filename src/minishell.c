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
	ft_alloc_init();
	signal_handlers_setup();
	env = (t_env *)ft_malloc(sizeof(t_env));
	copy_environment(env, envp);
	prompt = (t_prompt *)ft_malloc(sizeof(t_prompt));
	prompt->line = NULL;
	prompt->rebuild = 1;
	while (1)
	{
		scanner = (t_scanner *)ft_malloc(sizeof(t_scanner));
		error = (t_errors *)ft_malloc(sizeof(t_errors));
		scanner->command = input_get(prompt);									// get user's input command and store it in scanner->command
		head = NULL;
		return_value = ft_check(scanner, prompt, error);
		if (return_value == 1)
			exit(1);
		if (return_value != 2)
		{
			parsed_commands = input_process(scanner, head, error, prompt);// parse the command and store it in t_parser struct
			free(scanner->command);
			if (parsed_commands)
				chose_execution(parsed_commands, env);
			ft_free_parser(parsed_commands);
		}
		ft_free(scanner);
		ft_free(error);
	}
	ft_free(prompt);
	ft_destructor();
	return (0);
}
