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

t_env *env;
int	main(int argc, char **argv, char **envp)
{
	t_scanner	*scanner;
	t_prompt	*prompt;
	t_dlist		*head;
	t_errors	*error;
	int			return_value;
	t_parser	*parsed_commands;
	
	(void)argc;
	(void)argv;
	ft_alloc_init();
	signal_handlers_setup();
	env = (t_env *)ft_malloc(sizeof(t_env));
	copy_environment(envp);
	prompt = (t_prompt *)ft_malloc(sizeof(t_prompt));
	prompt->line = NULL;
	prompt->rebuild = 1;
	while (1)
	{
		scanner = (t_scanner *)ft_malloc(sizeof(t_scanner));
		error = (t_errors *)ft_malloc(sizeof(t_errors));
		scanner->command = input_get(prompt);
		if (strcmp(scanner->command, "exit") == 0)
		{
			printf("exit\n");
		    ft_free(prompt);
			free(scanner->command);
    		ft_destructor();
    		exit(EXIT_SUCCESS);
		}
		head = NULL;
		return_value = ft_check(scanner, prompt, error);
		if (return_value == 1)
			minishell_exit(1);
		if (return_value != 2)
		{
			parsed_commands = input_process(scanner, head, error, prompt);// parse the command and store it in t_parser struct
			free(scanner->command);
			if (parsed_commands)
				chose_execution(parsed_commands);
			ft_free_parser(parsed_commands);
		}
		ft_free(scanner);
		ft_free(error);
	}
	ft_free(prompt);
	ft_destructor();
	return (0);
}
