/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:09:03 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/18 21:32:42 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	copy_environment(char **envp)
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
	if (!env->all_vars)
		minishell_exit(1);
	i = 0;
	while (envp[i] != NULL)
	{
		env->all_vars[i] = ft_strdup(envp[i]);
		i++;
	}
	env->all_vars[i] = NULL;
}

void	change_variable(char *key, char *new_value)
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

int	print_env(t_parser *cmd)
{
	int		i;
	char	*equals_sign;

	i = 0;
	if (cmd->file)
		return (0);
	while (env->all_vars[i] != NULL)
	{
		equals_sign = ft_strchr(env->all_vars[i], '=');
		if (equals_sign)
			printf("%s\n", env->all_vars[i]);
		i++;
	}
	return (1);
}
