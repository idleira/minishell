/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:48:35 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/17 15:20:00 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_parser(t_parser *head)
{
	t_parser	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		ft_free(tmp->args);
		ft_free(tmp);
	}
}

void	ft_free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i])
	{
		ft_free(split[i]);
		i++;
	}
	ft_free(split);
}

char	*my_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (*s1)
	{
		result[i++] = *s1;
		s1++;
	}
	while (*s2)
	{
		result[i++] = *s2;
		s2++;
	}
	result[i++] = '\0';
	return (result);
}

void	check_builtin_and_red(t_parser *cmd)
{
	char	*cmd_w_path;
	pid_t	pid;
	int		status;

	if (!check_builtins(cmd))
	{
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
		{
			handle_redirection(cmd);
			cmd_w_path = get_path(cmd->args[0]);
			if (!cmd_w_path || (execve(cmd_w_path,
						cmd->args, env->all_vars) == -1))
			{
				printf("command not found: %s\n", cmd_w_path);
				env->exit_status = 127;
				return ;
			}
			//change to proper exit
			exit(0);
		}
		else
			waitpid(pid, &status, 0);
	}
}

void	minishell_exit(int status)
{
	env->exit_status = status;
	return ;
}
