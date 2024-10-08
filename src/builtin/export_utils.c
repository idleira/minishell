/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:17:01 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 16:17:01 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_var_value(char *var_name)
{
	int		i;
	size_t	var_name_len;

	i = 0;
	var_name_len = ft_strlen(var_name);
	while (g_env->all_vars[i] != NULL)
	{
		if ((ft_strncmp(g_env->all_vars[i], var_name, var_name_len) == 0)
			&& g_env->all_vars[i][var_name_len] == '=')
		{
			return (g_env->all_vars[i] + var_name_len + 1);
		}
		i++;
	}
	return (NULL);
}

char	*get_var_name(char *var)
{
	int		i;
	char	*name;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	name = ft_malloc(sizeof(char) * (i + 1));
	if (name == NULL)
		return (NULL);
	ft_strlcpy(name, var, i + 1);
	name[i] = '\0';
	return (name);
}

void	add_to_env(char *new_val)
{
	int		len;
	char	*new_var;

	len = 0;
	while (g_env->all_vars[len] != NULL)
		len++;
	if (ft_strchr(new_val, '=') == NULL)
	{
		new_var = my_strjoin(new_val, "=''");
		if (new_var == NULL)
			return ;
	}
	else
	{
		new_var = ft_strdup(new_val);
		if (new_var == NULL)
			return ;
	}
	reallocate_env(len, new_var);
}

void	reallocate_env(int len, char *new_var)
{
	char	**new_env_vars;
	int		i;

	i = 0;
	new_env_vars = (char **)ft_malloc(sizeof(char *) * (len + 2));
	if (new_env_vars == NULL)
		return (ft_free(new_var));
	while (i < len)
	{
		new_env_vars[i] = g_env->all_vars[i];
		i++;
	}
	new_env_vars[len] = new_var;
	new_env_vars[len + 1] = NULL;
	ft_free(g_env->all_vars);
	g_env->all_vars = new_env_vars;
}

char	**copy_env_to_export(char **temp_export)
{
	int	len;

	len = 0;
	while (g_env->all_vars[len] != NULL)
		len++;
	temp_export = ft_malloc((len + 1) * sizeof(char *));
	if (!temp_export)
		minishell_exit(1, false);
	len = 0;
	while (g_env->all_vars[len] != NULL)
	{
		temp_export[len] = ft_strdup(g_env->all_vars[len]);
		len++;
	}
	temp_export[len] = NULL;
	return (temp_export);
}
