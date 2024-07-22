/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 20:09:19 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/22 16:15:58 by mzhukova         ###   ########.fr       */
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

void	save_status_in_pipeline(int last_pid, pid_t pid)
{
	int	status;

	status = 0;
	while (wait(&status) > 0)
		continue ;
	if (last_pid != -1)
		save_status(pid, status);
}
