/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:52:34 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/07/27 00:54:35 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	signal_handlers_setup(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

// handles the signal SIGINT
void	signal_handler(int signum)
{
	int	status;

	if (signum == SIGINT && wait(&status) == -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		env->exit_status = 130;
	}
}
