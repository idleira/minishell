/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:27:54 by mzhukova          #+#    #+#             */
/*   Updated: 2024/06/24 16:52:58 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO:
//1. function check_builtins() that is called inside execute_command()
// Before execution check_builtins() checks the keyword and then calls the needed builtin function
int check_builtins(t_parser *cmd, t_env *env)
{
	if (cmd->args[0] && ft_strncmp(cmd->args[0], "cd", 2) == 0)
	{
		change_directory(cmd, env);
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
		if (chdir(env->home) == 0)
			env->pwd = ft_strdup(env->home);
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
			env->old_pwd = temp;
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
			env->pwd = ft_strdup(buffer); // Remember to free old env->pwd later
		}
		else
			perror("getcwd");
	}
	else
		printf("No such file or directory\n");
}