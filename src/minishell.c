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
	t_shell		*minishell;
	int			return_value;
	t_parser	*parsed_commands;
	
	(void)argc;
	(void)argv;
	minishell = (t_shell *)ft_malloc(sizeof(t_shell));
	ft_alloc_init();
	signal_handlers_setup();
	env = (t_env *)ft_malloc(sizeof(t_env));
	copy_environment(envp);
	minishell->prompt = (t_prompt *)ft_malloc(sizeof(t_prompt));
	minishell->prompt->line = NULL;
	minishell->prompt->rebuild = 1;
	while (1)
	{
		minishell->scanner = (t_scanner *)ft_malloc(sizeof(t_scanner));
		minishell->error = (t_errors *)ft_malloc(sizeof(t_errors));
		minishell->parser = (t_parser *)ft_malloc(sizeof(t_parser));
		minishell->scanner->command = input_get(minishell->prompt);
		// if (strcmp(scanner->command, "exit") == 0)
		// {
		// 	printf("exit\n");
		//     ft_free(prompt);
		// 	free(scanner->command);
		// 	ft_free_env();
    	// 	ft_destructor();
    	// 	exit(EXIT_SUCCESS);
		// }
		minishell->lexer = NULL;
		return_value = ft_check(minishell->scanner, minishell->prompt, minishell->error);
		if (return_value == 1)
			minishell_exit(1, false);
		if (return_value != 2)
		{
			parsed_commands = input_process(minishell);// parse the command and store it in t_parser struct
			free(minishell->scanner->command);
			if (parsed_commands)
				chose_execution(parsed_commands);
			ft_free_parser(parsed_commands);
		}
		ft_free(minishell->scanner);
		ft_free(minishell->error);
	}
	ft_free(minishell->prompt);
	ft_destructor();
	ft_free_split(env->all_vars);
	return (0);
}
