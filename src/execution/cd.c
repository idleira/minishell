/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:27:54 by mzhukova          #+#    #+#             */
/*   Updated: 2024/06/20 14:53:20 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//TODO:
//1. function check_builtins() that is called inside execute_command()
// Before execution check_builtins() checks the keyword and then calls the needed builtin function
void check_builtins(t_parser *cmd, t_env *env)
{
	//first check with first arg, then check how to fix it so it works from every position
	if (ft_strnstr(cmd->args[0], "cd", 2))
		change_directory(cmd, env);
}


void change_directory(t_parser *cmd, t_env *env)
{
	char *cd_path;

	int i = 0;
	
	while (cmd->args[i])
	{
		if (ft_strnstr(cmd->args[i], "cd", 2) == 0)
		{
			
			cd_path = my_strjoin(cd_path, cmd->args[i]);
		}
		printf("check adding cd %s\n", cd_path); 
		i++;
	}
	env->old_pwd = env->pwd;
	cd_path = my_strjoin(env->pwd, cd_path);
	printf("current_path: %s\n", cd_path);
	if (chdir(cd_path) < 0)
		printf("error cd\n");
	//env->pwd = 
	
}