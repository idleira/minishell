/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:09:19 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/26 20:28:09 by mzhukova         ###   ########.fr       */
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

int	check_exit(t_parser *cmd)
{
	if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
	{
		printf("exit\n");
		if (!(cmd->args[1]))
			env->exit_status = 0;
		else if (cmd->args[1] && !cmd->args[2])
		{
			if (ft_isnum(cmd->args[1]))
				env->exit_status = ft_atoi(cmd->args[1]);
			else
			{
				printf("exit: %s: numeric argument required\n", cmd->args[1]);
				env->exit_status = 2;
			}
		}
		else
		{
			printf("exit: too many arguments\n");
			env->exit_status = 1;
			return (0);
		}
		free_in_exit();
	}
	return (1);
}


void	free_in_exit(void)
{
	int	exit;

	exit = env->exit_status;
		// ft_free(prompt); these will be added when we create a global struct
	// free(scanner->command); these will be added when we create a global struct
	//ft_free_env(); delete this function
	ft_destructor();
	_exit(exit);
}
