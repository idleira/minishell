/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_intit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:17:34 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 16:17:34 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	find_equal_index(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '=' && string[i])
		i++;
	return (i);
}

t_env	*env_list_create(t_env	*env, char **envp)
{
	int		i;
	t_env	*traveser;

	i = 0;
	env = ft_lstnew();
	traveser = env;
	while (envp[i])
	{
		traveser->key = ft_substr(envp[i], 0, find_equal_index(envp[i]));
		traveser->value = ft_substr(envp[i],
				find_equal_index(envp[i]) + 1, ft_strlen(envp[i]));
		if (envp[i + 1])
			ft_lstadd_back(&env, ft_lstnew());
		traveser = traveser->next;
		i++;
	}
	return (env);
}

// t_env	*env_list_create(t_env	*env, char **envp)
// {
// 	int		i;
// 	t_env	*head;
// 	t_env	*node;

// 	i = 0;
// 	(void)env;
// 	while (envp[i])
// 	{
// 		node = ft_lstnew();
// 		node->key = ft_substr(envp[i], 0, find_equal_index(envp[i]));
// 		node->value = ft_substr(envp[i],
// 				find_equal_index(envp[i]) + 1, ft_strlen(envp[i]));
// 		ft_lstadd_back(&head, node);
// 		i++;
// 	}
// 	return (head);
// }