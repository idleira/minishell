/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:07:37 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/27 15:53:39 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_var_index(char *var, char **all_vars)
{
	int	i;

	i = 0;
	while (all_vars[i])
	{
		if (ft_strncmp(var, all_vars[i], ft_strlen(var)) == 0
			&& all_vars[i][ft_strlen(var)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	unset_var(t_parser *cmd)
{
	int		index;
	int		len;
	char	**new_all_vars;
	int		i;

	len = 0;
	while (g_env->all_vars[len] != NULL)
		len++;
	i = 1;
	while (cmd->args[i])
	{
		index = find_var_index(cmd->args[i], g_env->all_vars);
		if (index == -1)
			return (1);
		new_all_vars = copy_new_export(g_env->all_vars, index, len);
		if (new_all_vars == NULL)
			return (1);
		ft_free(g_env->all_vars[index]);
		ft_free(g_env->all_vars);
		g_env->all_vars = new_all_vars;
		i++;
	}
	return (1);
}

char	**copy_new_export(char **all_vars, int exclude_index, int len)
{
	char	**new_all_vars;
	int		i;
	int		j;

	new_all_vars = (char **)ft_malloc(sizeof(char *) * len);
	if (new_all_vars == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i != exclude_index)
			new_all_vars[j++] = all_vars[i];
		i++;
	}
	new_all_vars[j] = NULL;
	return (new_all_vars);
}
