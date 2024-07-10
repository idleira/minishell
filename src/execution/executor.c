/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:13 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/10 17:37:12 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	chose_execution(t_parser *head, t_env *env)
{
	if (head && head->next)
		execute_pipeline(head, env);
	else if (head)
		execute_command(head, env);
}

char	*get_path(char *cmd, t_env *env)
{
	char	*temp_path;
	char	*cmd_path;
	int		i;

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
	return (NULL);
}

void	execute_command(t_parser *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*cmd_w_path;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		if (!check_builtins(cmd, env))
		{
			handle_redirection(cmd);
			cmd_w_path = get_path(cmd->args[0], env);
			if (execve(cmd_w_path, cmd->args, env->all_vars) == -1)
			{
				perror("command not found");
				ft_destructor();
				exit(EXIT_FAILURE);
			}
			printf("execution just got handled\n");
		}
	}
	else
		waitpid(pid, &status, 0);
}



void	handle_redirection(t_parser *cmd)
{
	t_list	*file;

	file = cmd->file;
	while (file)
	{
		if (file->type == '|')
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
			exit(EXIT_FAILURE);
		}
		if (file->type == '<')
			dup2(cmd->fd, STDIN_FILENO);
		else
			dup2(cmd->fd, STDOUT_FILENO);
		close(cmd->fd);
		file = file->next;
	}
}

void execute_pipeline(t_parser *head, t_env *env)
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
			if (!check_builtins(current, env))
			{
				cmd_w_path = get_path(current->args[0], env);
				if (cmd_w_path == NULL)
				{
					printf("Command not found: \n");
					exit(EXIT_FAILURE);
				}
				if (execve(cmd_w_path, current->args, env->all_vars) == -1)
				{
					perror("execve");
					ft_free(cmd_w_path);
					exit(EXIT_FAILURE);
				}
			}
			else
				exit(EXIT_SUCCESS);
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


