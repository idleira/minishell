/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 19:27:54 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/31 00:02:00 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_builtins(t_parser *cmd)
{
	if (cmd->args[0] && ft_strcmp(cmd->args[0], "cd") == 0)
	{
		change_directory(cmd);
		return (1);
	}
	else if (cmd->args[0] && ft_strcmp(cmd->args[0], "env") == 0)
		return (print_env(cmd));
	else if (cmd->args[0] && ft_strcmp(cmd->args[0], "pwd") == 0)
	{
		if (cmd->file)
			return (0);
		else
			return (printf("%s\n", g_env->pwd));
	}
	else if (cmd->args[0] && ft_strcmp(cmd->args[0], "export") == 0)
		return (check_export(cmd));
	else if (cmd->args[0] && ft_strcmp(cmd->args[0], "echo") == 0)
		return (check_echo(cmd));
	else if (cmd->args[0] && ft_strcmp(cmd->args[0], "unset") == 0)
		return (unset_var(cmd));
	return (0);
}

void	change_directory(t_parser *cmd)
{
	if (!cmd->args[1] || (cmd->args[1][0] == '~' && !cmd->args[1][1]))
	{
		g_env->old_pwd = g_env->pwd;
		change_variable("OLDPWD=", g_env->old_pwd);
		if (chdir(g_env->home) == 0)
		{
			g_env->pwd = ft_strdup(g_env->home);
			change_variable("PWD=", g_env->pwd);
		}
		else
			perror("chdir");
		return ;
	}
	if (ft_strncmp(cmd->args[1], "-", 1) == 0)
		return (handle_slash_return());
	construct_cd_path(cmd);
}

void	construct_cd_path(t_parser *cmd)
{
	char	*cd_path;
	char	buffer[4096];

	cd_path = cmd->args[1];
	if (chdir(cd_path) == 0)
	{
		if (getcwd(buffer, sizeof(buffer)) != NULL)
		{
			g_env->old_pwd = g_env->pwd;
			g_env->pwd = ft_strdup(buffer);
			change_variable("PWD=", g_env->pwd);
			change_variable("OLDPWD=", g_env->old_pwd);
		}
		else
			perror("getcwd");
	}
	else
		printf("cd: %s: No such file or directory\n", cmd->args[1]);
}

void	handle_slash_return(void)
{
	char	*temp;

	printf("%s\n", g_env->old_pwd);
	if (chdir(g_env->old_pwd) == 0)
	{
		temp = g_env->pwd;
		g_env->pwd = g_env->old_pwd;
		change_variable("PWD=", g_env->old_pwd);
		g_env->old_pwd = temp;
		change_variable("OLDPWD=", temp);
	}
	else
		perror("chdir");
	return ;
}
