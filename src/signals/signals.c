/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:52:34 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/06/24 17:24:44 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// sets up signal handlers for SIGINT(request to interrupt the process) and SIGQUIT(request to quit the process)
void signal_handlers_setup(void)
{
	printf("signal_handlers_setup\n");
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

// handles the signal SIGINT
void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("ctrl+c pressed\n");
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}