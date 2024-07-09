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

// gets the index of the first '=' in a string
// static int	get_v(char *string)
// {
// 	int	i;

// 	i = 0;
// 	while (string[i] != '=' && string[i])
// 		i++;
// 	return (i);
// }

// // initializes environment variables by adding to a pre-existing list
// t_env	*env_init(t_env	*env, char **envp)
// {
// 	int		i;
// 	t_env	*traveser;

// 	i = 0;
// 	env = ft_lstnew();
// 	traveser = env;
// 	while (envp[i])
// 	{
// 		traveser->key = ft_substr(envp[i], 0, get_v(envp[i]));
// 		traveser->value = ft_substr(envp[i],
// 				get_v(envp[i]) + 1, ft_strlen(envp[i]));
// 		if (envp[i + 1])
// 			ft_lstadd_back(&env, ft_lstnew());
// 		traveser = traveser->next;
// 		i++;
// 	}
// 	return (env);
// }

// initializes environment variables by creating a new list
// t_env	*env_init(t_env	*env, char **envp)
// {
// 	int		i;
// 	t_env	*head;
// 	t_env	*node;

// 	i = 0;
// 	(void)env;
// 	while (envp[i])
// 	{
// 		node = ft_lstnew();
// 		node->key = ft_substr(envp[i], 0, get_v(envp[i]));
// 		node->value = ft_substr(envp[i],
// 				get_v(envp[i]) + 1, ft_strlen(envp[i]));
// 		ft_lstadd_back(&head, node);
// 		i++;
// 	}
// 	return (head);
// }