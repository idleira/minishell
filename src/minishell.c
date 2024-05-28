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

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		if (!prompt)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		scanner = (t_scanner *)malloc(sizeof(t_scanner));
		error = (t_errors *)malloc(sizeof(t_errors));
		scanner->command = input_get(prompt);
		if (!scanner->command)
		{
			fprintf(stderr, "input_get returned NULL\n");
			exit(EXIT_FAILURE);
		}
		printf("command: %s\n", scanner->command);
		head = NULL;
		return_value = check_cmd_empty(scanner, prompt);
		if (return_value == 1)
			exit(1);
		if (!(return_value == 2))
			error_parse_handle(scanner, head, error, prompt);
	}
	return (0);
}
