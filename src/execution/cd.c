/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:27:54 by mzhukova          #+#    #+#             */
/*   Updated: 2024/06/21 16:59:46 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO:
//1. function check_builtins() that is called inside execute_command()
// Before execution check_builtins() checks the keyword and then calls the needed builtin function
int check_builtins(t_parser *cmd, t_env *env)
{
	//first check with first arg, then check how to fix it so it works from every position
	if (ft_strnstr(cmd->args[0], "cd", 2))
	{
		if (ft_strlen(cmd->args[0]) > 2)
		{
			printf("command not found\n");
			return (1);
		}
		change_directory(cmd, env);
		return (1);
	}
	return (0);
}


void change_directory(t_parser *cmd, t_env *env)
{
	char	*cd_path;
	char	buffer[4096];

	int i = 0;
	cd_path = "";
	if (!cmd->args[1] || (cmd->args[1][0] == '~' && !cmd->args[2]))
	{
		env->old_pwd = env->pwd;
		env->pwd = env->home;
		chdir(env->home);
		return ;
		
	}
	while (cmd->args[i])
	{
		if (ft_strnstr(cmd->args[i], "cd", 2) == 0)
		{
			if (ft_strnstr(cmd->args[1], "-", 1) != 0)
			{
				printf("%s\n", env->old_pwd);
				if (chdir(env->old_pwd) != 0)
					printf("No such file or directory\n");
				env->pwd = env->old_pwd;
				return ;
			}

			cd_path = my_strjoin(cd_path, cmd->args[i]);
		}
		i++;
	}
	//env->old_pwd = env->pwd;
	if (cd_path[0] != '/')
		cd_path = my_strjoin("/", cd_path);
	if (cd_path[ft_strlen(cd_path)] != '/')
		cd_path = my_strjoin(cd_path, "/");
	cd_path = my_strjoin(env->pwd, cd_path);
	if (chdir(cd_path) == 0)
    {
        if (getcwd(buffer, sizeof(buffer)) != NULL)
		{
        	env->pwd = ft_strdup(buffer); //free this later
		}
    }
	else
		printf("No such file or directory, return\n");
	env->old_pwd = env->pwd;
}