/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:09:03 by mzhukova          #+#    #+#             */
/*   Updated: 2024/06/12 19:24:23 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void copy_environment(t_env *env, char **envp)
{
	int	i;
	int	envp_count;
	
	env->pwd = getenv("PWD");
	env->old_pwd = getenv("OLDPWD");
	env->home = getenv("HOME");
	env->paths = ft_split(getenv("PATH"), ':');
	envp_count = 0;
	while (envp[envp_count] != NULL)
		envp_count++;
	env->all_vars = malloc((envp_count + 1) * sizeof(char *));
	// Handle the exit properly later ->
	if (!env->all_vars)
		exit(1);
	i = 0;
	while (envp[i] != NULL)
	{
		env->all_vars[i] = ft_strdup(envp[i]);
		i++;
	}
	env->all_vars[i] = NULL;
}