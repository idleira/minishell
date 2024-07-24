/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:26:25 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/24 14:25:20 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_export(void)
{
	int		i;
	int		size;
	char	**temp_export;
	char	*temp_name;

	i = 0;
	size = 0;
	temp_export = NULL;
	while (env->all_vars[size])
		size++;
	temp_export = copy_env_to_export(temp_export);
	sort_env_vars(temp_export, size);
	while (temp_export[i] != NULL)
	{
		temp_name = get_var_name(temp_export[i]);
		if (ft_strnstr(temp_export[i], "=''", ft_strlen(temp_export[i])))
			printf("declare -x %s\n", temp_name);
		else
			printf("declare -x %s=\"%s\"\n", get_var_name(temp_export[i]),
				get_var_value(temp_name));
		free (temp_name);
		i++;
	}
	ft_free_split(temp_export);
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
	char	*new_var_name;

	i = 0;
	new_var_name = get_var_name(var);
	while (env->all_vars[i] != NULL)
	{
		var_name = get_var_name(env->all_vars[i]);
		if ((ft_strncmp(var_name, new_var_name, ft_strlen(var_name)) == 0)
			&& (ft_strlen(var_name) == ft_strlen(new_var_name)))
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
		if (ft_strncmp(current_name, var_name, ft_strlen(current_name)) == 0)
		{
			if (ft_strchr(var, '=') != NULL)
			{
				ft_free(env->all_vars[i]);
				env->all_vars[i] = ft_strdup(var);
			}
			break ;
		}
		ft_free(current_name);
		i++;
	}
	ft_free(var_name);
}
