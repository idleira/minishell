/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:09:03 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/27 15:43:56 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	copy_environment(char **envp)
{
	int	i;
	int	envp_count;

	g_env->pwd = getenv("PWD");
	g_env->old_pwd = getenv("OLDPWD");
	g_env->home = getenv("HOME");
	g_env->user = getenv("USER");
	g_env->paths = ft_split(getenv("PATH"), ':');
	envp_count = 0;
	while (envp[envp_count] != NULL)
		envp_count++;
	g_env->all_vars = ft_malloc((envp_count + 1) * sizeof(char *));
	if (!g_env->all_vars)
		minishell_exit(1, false);
	i = 0;
	while (envp[i] != NULL)
	{
		g_env->all_vars[i] = ft_strdup(envp[i]);
		i++;
	}
	g_env->all_vars[i] = NULL;
	g_env->all_vars[i - 1] = ft_strdup("_=/usr/bin/env");
}

void	ft_free_env(void)
{
	int	i;

	if (g_env->all_vars == NULL)
		return ;
	i = 0;
	while (g_env->all_vars[i])
	{
		ft_free(g_env->all_vars[i]);
		i++;
	}
	free(g_env->all_vars);
}

void	change_variable(char *key, char *new_value)
{
	int	i;

	i = 0;
	while (g_env->all_vars[i] != NULL)
	{
		if (ft_strncmp(g_env->all_vars[i], key, ft_strlen(key)) == 0)
		{
			ft_free(g_env->all_vars[i]);
			g_env->all_vars[i] = ft_strdup(key);
			g_env->all_vars[i] = my_strjoin(g_env->all_vars[i], new_value);
		}
		i++;
	}
}

int	print_env(t_parser *cmd)
{
	int		i;
	char	*equals_sign;
	char	*unset;

	i = 0;
	if (cmd->file)
		return (0);
	while (g_env->all_vars[i] != NULL)
	{
		equals_sign = ft_strchr(g_env->all_vars[i], '=');
		unset = ft_strnstr(g_env->all_vars[i], "=''",
				ft_strlen(g_env->all_vars[i]));
		if (equals_sign && (!unset))
			printf("%s\n", g_env->all_vars[i]);
		i++;
	}
	return (1);
}
