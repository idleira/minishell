/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:09:03 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/08 14:52:48 by mzhukova         ###   ########.fr       */
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
	env->all_vars = ft_malloc((envp_count + 1) * sizeof(char *));
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

void change_variable(t_env *env, char *key, char *new_value)
{

	int	i;
	
	i = 0;
	while (env->all_vars[i] != NULL)
	{
		if (ft_strncmp(env->all_vars[i], key, ft_strlen(key)) == 0)
		{
			ft_free(env->all_vars[i]);
			env->all_vars[i] = ft_strdup(key);
			env->all_vars[i] = my_strjoin(env->all_vars[i], new_value);
		}
		i++;
	}

}

void print_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->all_vars[i] != NULL)
	{
		printf("%s\n", env->all_vars[i]);
		i++;
	}
	
}