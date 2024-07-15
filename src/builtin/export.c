/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:26:25 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/15 18:37:12 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_export()
{
	int		i;
	int		size;
	char	*equals_sign;

	i = 0;
	size = 0;
	while (env->all_vars[size])
		size++;
	sort_env_vars(env->all_vars, size);
	while (env->all_vars[i] != NULL)
	{
		equals_sign = ft_strchr(env->all_vars[i], '=');
		if (equals_sign != NULL)
			printf("declare -x %s\n", env->all_vars[i]);
		else
			printf("declare -x %s=''\n", env->all_vars[i]);
		i++;
	}
	return (1);
}

int	check_export(t_parser *cmd)
{
	int	i;

	i = 1;
	if (cmd->file)
		return (0);
	if (cmd->args[1] == NULL)
		return (print_export());
	while (cmd->args[i])
	{
		if (is_valid_argument(cmd->args[i]))
		{
			if (exists_in_env(cmd->args[i]))
				update_env(cmd->args[i]);
			else
				add_to_env(cmd->args[i]);
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

int	is_valid_argument(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (0);
	i = 1;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	exists_in_env(char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	while (env->all_vars[i] != NULL)
	{
		var_name = get_var_name(env->all_vars[i]);
		if (ft_strncmp(var_name, var, ft_strlen(var)) == 0)
		{
			ft_free(var_name);
			return (1);
		}
		ft_free(var_name);
		i++;
	}
	return (0);
}

void	update_env(char *var)
{
	int		i;
	char	*var_name;
	char	*current_name;

	var_name = get_var_name(var);
	i = 0;
	while (env->all_vars[i] != NULL)
	{
		current_name = get_var_name(env->all_vars[i]);
		if (ft_strncmp(current_name, var_name, i) == 0)
		{
			ft_free(env->all_vars[i]);
			env->all_vars[i] = ft_strdup(var);
			ft_free(current_name);
			break ;
		}
		ft_free(current_name);
		i++;
	}
	ft_free(var_name);
}
