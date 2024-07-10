/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:27:54 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/10 14:34:47 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int check_builtins(t_parser *cmd, t_env *env)
{
	if (cmd->args[0] && ft_strncmp(cmd->args[0], "cd", 2) == 0)
	{
		change_directory(cmd, env);
		return (1);
	}
	else if (cmd->args[0] && ft_strncmp(cmd->args[0], "env", 3) == 0)
		return (print_env(cmd, env));
	else if (cmd->args[0] && ft_strncmp(cmd->args[0], "pwd", 3) == 0)
	{
		if (cmd->file)
			return (0);
		else
			return (printf("%s\n", env->pwd));
	}
	else if (cmd->args[0] && ft_strncmp(cmd->args[0], "export", 6) == 0)
		return check_export(cmd, env);
	else if (cmd->args[0] && ft_strncmp(cmd->args[0], "echo", 4) == 0)
		return (check_echo(cmd, env));
	else if (cmd->args[0] && ft_strncmp(cmd->args[0], "unset", 5) == 0)
	{
		(unset_var(cmd, env));
		return (1);
	}
	return (0);
}


void change_directory(t_parser *cmd, t_env *env)
{
	char *cd_path;
	char buffer[4096];

	// Handle 'cd' with no arguments or 'cd ~'
	if (!cmd->args[1] || (cmd->args[1][0] == '~' && !cmd->args[1][1]))
	{
		env->old_pwd = env->pwd;
		change_variable(env, "OLDPWD=", env->old_pwd);
		if (chdir(env->home) == 0)
		{
			env->pwd = ft_strdup(env->home);
			change_variable(env, "PWD=", env->pwd);
		}
		else
			perror("chdir");
		return;
	}

	// Handle 'cd -'
	if (ft_strncmp(cmd->args[1], "-", 1) == 0)
	{
		printf("%s\n", env->old_pwd);
		if (chdir(env->old_pwd) == 0)
		{
			char *temp = env->pwd;
			env->pwd = env->old_pwd;
			change_variable(env, "PWD=", env->old_pwd);
			env->old_pwd = temp;
			change_variable(env, "OLDPWD=", temp);
		}
		else
			perror("chdir");
		return;
	}

	// Construct the target path
	cd_path = cmd->args[1];
	if (chdir(cd_path) == 0)
	{
		if (getcwd(buffer, sizeof(buffer)) != NULL)
		{
			env->old_pwd = env->pwd;
			env->pwd = ft_strdup(buffer); // Remember to ft_free old env->pwd later
			change_variable(env, "PWD=", env->pwd);
			change_variable(env, "OLDPWD=", env->old_pwd);
		}
		else
			perror("getcwd");
	}
	else
	{
		printf("No such file or directory\n");
	}
}