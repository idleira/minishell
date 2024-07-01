/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:26:25 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/01 17:39:58 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void print_export(t_env *env)
{
	int		i;
	char	*equals_sign;

	i = 0;
	while (env->all_vars[i] != NULL)
	{
		equals_sign = ft_strchr(env->all_vars[i], '=');
		if (equals_sign != NULL)
			printf("declare -x %s\n", env->all_vars[i]);
		else
			printf("declare -x %s=''\n", env->all_vars[i]);
		i++;
	}
}

void add_to_env(t_env *env, char *new_val)
{
	int		len;
	char	*new_var;

	len = 0;
	while (env->all_vars[len] != NULL)
		len++;
	if (ft_strchr(new_val, '=') == NULL)
	{
		new_var = my_strjoin(new_val, "=''");
		if (new_var == NULL)
			return;
	}
	else
	{
		new_var = ft_strdup(new_val);
		if (new_var == NULL)
			return;
	}
	env->all_vars = realloc(env->all_vars, sizeof(char *) * (len + 2));
	if (env->all_vars == NULL)
	{
		free(new_var);
		return;
	}
	env->all_vars[len] = new_var;
	env->all_vars[len + 1] = NULL;
}

int check_export(t_parser *cmd, t_env *env)
{
	int i = 1;
	if (cmd->args[1] == NULL)
	{
		print_export(env);
		return (1);
	}
	while (cmd->args[i])
	{
		if (is_valid_argument(cmd->args[i]))
		{
			if (exists_in_env(env, cmd->args[i]))
				update_env(env, cmd->args[i]);
			else
				add_to_env(env, cmd->args[i]);
		}
		else
		{
			perror(cmd->args[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int is_valid_argument(char *arg)
{
	int i;

	i = 0;
	if (arg == NULL)
		return 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return 0;
	i = 1;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return 0;
		i++;
	}
	return 1;
}

int	exists_in_env(t_env *env, char *var)
{
	int	i;
	
	i = 0;
	while (env->all_vars[i] != NULL)
	{
		char *var_name = get_var_name(env->all_vars[i]);
		if (ft_strncmp(var_name, var, i) == 0)
		{
			free(var_name);
			return 1;
		}
		free(var_name);
		i++;
	}
	return 0;
}
char	*get_var_name(char *var)
{
	int i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	char *name = malloc(sizeof(char) * (i + 1));
	if (name == NULL)
		return NULL;
	ft_strlcpy(name, var, i + 1);
	name[i] = '\0';
	return (name);
}
void	update_env(t_env *env, char *var)
{
	int i = 0;
	char *var_name = get_var_name(var);
	while (env->all_vars[i] != NULL)
	{
		char *current_name = get_var_name(env->all_vars[i]);
	if (ft_strncmp(current_name, var_name, i) == 0)
		{
			free(env->all_vars[i]);
			env->all_vars[i] = ft_strdup(var);
			free(current_name);
			break;
		}
		free(current_name);
		i++;
	}
	free(var_name);
}

char *get_var_value(t_env *env, char *var_name)
{
	int	i;

	i = 0;
	size_t var_name_len = ft_strlen(var_name);

	while (env->all_vars[i] != NULL)
	{
		if (ft_strncmp(env->all_vars[i], var_name, var_name_len) == 0 && env->all_vars[i][var_name_len] == '=')
		{
			return env->all_vars[i] + var_name_len + 1;
		}
		i++;
	}
	return (NULL);
}