/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:15:23 by mzhukova          #+#    #+#             */
/*   Updated: 2024/07/17 15:16:16 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_pipeline(t_parser *head)
{
	int			pipefd[2];
	int			prev_fd;
	pid_t		pid;
	t_parser	*current;
	int			status;

	current = head;
	prev_fd = -1;
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			pipe_child(prev_fd, pipefd, current);
		else
			pipe_parent(prev_fd, pipefd, current);
	}
	while (wait(&status) > 0);
}

void	pipe_parent(int prev_fd, int pipefd[2], t_parser *current)
{
	if (prev_fd != -1)
		close(prev_fd);
	if (current->next)
	{
		close(pipefd[1]);
		prev_fd = pipefd[0];
	}
	else
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	current = current->next;
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
			env->exit_status = 127;
			exit(127);
		}
		if (execve(cmd_w_path, current->args, env->all_vars) == -1)
		{
			perror("execve");
			free(cmd_w_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		env->exit_status = 0;
		exit(0);
	}
}