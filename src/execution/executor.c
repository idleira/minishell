/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:13 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/16 18:27:53 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	chose_execution(t_parser *head)
{
	if (head && head->next)
		execute_pipeline(head);
	else if (head)
		execute_command(head);
}

char	*get_path(char *cmd)
{
	char	*temp_path;
	char	*cmd_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	while (env->paths[i])
	{
		temp_path = my_strjoin(env->paths[i], "/");
		cmd_path = my_strjoin(temp_path, cmd);
		ft_free(temp_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		ft_free(cmd_path);
		i++;
	}
	return (cmd);
}

void	execute_command(t_parser *cmd)
{
		check_builtin_and_red(cmd);
}

void	handle_redirection(t_parser *cmd)
{
	t_list	*file;

	file = cmd->file;
	while (file)
	{
		if ((file->type == '|') || (file->type == IN))
			cmd->fd = open(file->name, O_RDONLY);
		else if (file->type == OUT)
			cmd->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == APPEND)
			cmd->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd = -1;
		if (cmd->fd < 0)
		{
			perror("open file");
			minishell_exit(1);
		}
		if (file->type == IN)
			dup2(cmd->fd, STDIN_FILENO);
		else
			dup2(cmd->fd, STDOUT_FILENO);
		close(cmd->fd);
		file = file->next;
	}
}

void execute_pipeline(t_parser *head)
{
	int			pipefd[2];
	int			prev_fd;
	pid_t		pid;
	t_parser	*current;
	char		*cmd_w_path;

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
			if (!check_builtins(current))
			{
				cmd_w_path = get_path(current->args[0]);
				if (cmd_w_path == NULL)
				{
					printf("Command not found: \n");
					minishell_exit(127);
				}
				if (execve(cmd_w_path, current->args, env->all_vars) == -1)
				{
					perror("execve");
					ft_free(cmd_w_path);
					env->exit_status = 1;
					exit(env->exit_status);
				}
			}
			else
			{
				env->exit_status = 0;
				exit(env->exit_status);
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


