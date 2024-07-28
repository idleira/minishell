/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:15:23 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/27 15:47:35 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_pipeline(t_parser *head)
{
	int			pipefd[2];
	int			prev_fd;
	pid_t		pid;
	pid_t		last_pid;
	t_parser	*current;

	current = head;
	last_pid = -1;
	prev_fd = -1;
	while (current)
	{
		check_next(pipefd, current);
		pid = fork();
		if (pid == -1)
			error_fork();
		else if (pid == 0)
			pipe_child(prev_fd, pipefd, current);
		else
		{
			last_pid = pid;
			pipe_parent(&prev_fd, pipefd, current);
			current = current->next;
		}
	}
	save_status_in_pipeline(last_pid);
}

void	pipe_parent(int *prev_fd, int pipefd[2], t_parser *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	pipe_child(int prev_fd, int pipefd[2], t_parser *current)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	handle_redirection(current);
	check_built_and_exec(current);
}

void	check_built_and_exec(t_parser *current)
{
	char	*cmd_w_path;

	if (!check_builtins(current))
	{
		cmd_w_path = get_path(current->args[0]);
		if (cmd_w_path == NULL)
		{
			printf("command not found: %s\n", current->args[0]);
			g_env->exit_status = 127;
			exit(127);
		}
		if (execve(cmd_w_path, current->args, g_env->all_vars) == -1)
		{
			printf("command not found: %s\n", current->args[0]);
			g_env->exit_status = 127;
			free(cmd_w_path);
			exit(127);
		}
	}
	else
	{
		g_env->exit_status = 0;
		exit(0);
	}
}

void	check_next(int pipefd[2], t_parser *current)
{
	if (current->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			minishell_exit(1, true);
		}
	}
}
