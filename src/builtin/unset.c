/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:07:37 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/10 15:58:26 by mzhukova         ###   ########.fr       */
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

void	unset_var(t_parser *cmd, t_env *env)
{
	int		index;
	int		len;
	char	**new_all_vars;

	len = 0;
	while (env->all_vars[len] != NULL)
		len++;
	index = find_var_index(cmd->args[1], env->all_vars);
	if (index == -1)
		return ;
	new_all_vars = copy_new_export(env->all_vars, index, len);
	if (new_all_vars == NULL)
		return ;
	ft_free(env->all_vars[index]);
	ft_free(env->all_vars);
	env->all_vars = new_all_vars;
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