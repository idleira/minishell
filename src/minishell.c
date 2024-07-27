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

t_env	*g_env;

int	main(int argc, char **argv, char **envp)
{
	t_shell		*minishell;

	(void)argc;
	(void)argv;
	minishell = (t_shell *)ft_malloc(sizeof(t_shell));
	ft_alloc_init();
	signal_handlers_setup();
	g_env = (t_env *)ft_malloc(sizeof(t_env));
	copy_environment(envp);
	minishell->prompt = (t_prompt *)ft_malloc(sizeof(t_prompt));
	minishell->prompt->line = NULL;
	minishell->prompt->rebuild = 1;
	while (1)
		process_and_execute(minishell);
	ft_free(minishell->prompt);
	ft_destructor();
	//ft_free_split(g_env->all_vars);
	return (0);
}
