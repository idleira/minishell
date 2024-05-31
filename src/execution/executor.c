/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:13 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/05/30 16:22:30 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_command(t_parser *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_redirection(cmd);
		if (execvp(cmd->args[0], cmd->args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
		waitpid(pid, &status, 0);
}

void	handle_redirection(t_parser *cmd)
{
	t_list	*file;
	int		fd;

	file = cmd->file;
	while (file)
	{
		if (file->type == __RED_IN)
			fd = open(file->name, O_RDONLY);
		else if (file->type == __RED_OUT)
			fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == __RED_APP)
			fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = -1;
		if (fd < 0)
		{
			perror("open file");
			exit(EXIT_FAILURE);
		}
		if (file->type == __RED_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		file = file->next;
	}
}

void	chose_execution(t_parser *head)
{
	if (head && head->next)
		execute_pipeline(head);
	else if (head)
		execute_command(head);
}

void	execute_pipeline(t_parser *head)
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	t_parser	*current;

	prev_fd = -1;
	current = head;
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
			if (execvp(current->args[0], current->args) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (current->next)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			waitpid(pid, NULL, 0);
		}
		current = current->next;
	}
}

void free_parser(t_parser *head)
{
	t_parser *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->args);
		free(tmp);
	}
}