/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:09:03 by mzhukova          #+#    #+#             */
/*   Updated: 2024/06/12 18:53:28 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void copy_environment(t_env *env, char **envp)
{
	int	i;
	int	envp_count = 0;
	
	env->pwd = getenv("PWD");
	env->old_pwd = getenv("OLDPWD");
	env->home = getenv("HOME");
	env->paths = ft_split(getenv("PATH"), ':');
	while (envp[envp_count] != NULL)
		envp_count++;
	env->paths = malloc((envp_count + 1) * sizeof(char *));
	// Handle the exit properly later
	if (!env->paths)
		exit(1);
	i = 0;
	while (envp[i] != NULL)
	{
		env->paths[i] = ft_strdup(envp[i]);
		i++;
	}
	env->paths[i] = NULL; 
}