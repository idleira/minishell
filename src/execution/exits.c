/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:09:19 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/22 17:31:01 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	minishell_exit(int status, bool is_exit)
{
	env->exit_status = status;

	if (!is_exit)
		return ;
	_exit(status);
}

void	save_status(pid_t pid, int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		env->exit_status = WEXITSTATUS(status);
}

void	save_status_in_pipeline(int last_pid)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				env->exit_status = WEXITSTATUS(status);
		}
		pid = wait(&status);
	}
}

// do it here or using t_parser???
// void check_exit(t_scanner *scanner, t_prompt *prompt)
// {
// 	if (strcmp(scanner->command, "exit") == 0)
// 	{
// 		if (second arg)
// 			if !isnum()
// 				printf(bash: exit: ghghg: numeric argument required) && exit
// 			env->exit_status = second arg;
// 		else if (second arg && 3rd arg)
// 			printf(bash: exit: too many arguments) && exit
// 		printf("exit\n");
// 		ft_free(prompt);
// 		free(scanner->command);
// 		ft_free_env();
// 		ft_destructor();
// 		exit(EXIT_SUCCESS);
// 	}
// }