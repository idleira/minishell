/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:13 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/06/19 20:15:29 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char *get_path(char *cmd, t_env *env)
{
	char	*temp_path;
	char	*cmd_path;
	int		i;
	
	i = 0;
	while (env->paths[i])
	{
		temp_path = my_strjoin(env->paths[i], "/");
		cmd_path = my_strjoin(temp_path, cmd);
		
		free(temp_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
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
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		handle_redirection(cmd);
		cmd_w_path = get_path(cmd->args[0], env);
		if (execve(cmd_w_path, cmd->args, env->all_vars) == -1)
		{
			perror("execve");
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
		if (file->type == '|')
			fd = open(file->name, O_RDONLY);
		else if (file->type == OUT)
		{
			fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (file->type == APPEND)
			fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = -1;
		if (fd < 0)
		{
			perror("open file");
			exit(EXIT_FAILURE);
		}
		if (file->type == '<')
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		file = file->next;
	}
}

void	chose_execution(t_parser *head, t_env *env)
{
	if (head && head->next)
		execute_pipeline(head, env);
	else if (head)
		execute_command(head, env);
}

void	execute_pipeline(t_parser *head, t_env *env)
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
			cmd_w_path = get_path(current->args[0], env);
			if (execve(cmd_w_path, current->args, env->all_vars) == -1)
			{
				perror("execve");
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

void	free_split(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*my_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
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