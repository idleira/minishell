/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:13 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/23 17:18:38 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	chose_execution(t_parser *head)
{
	if (!check_exit(head))
		return (minishell_exit(env->exit_status, false));
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
		else if (file->type == HEREDOC)
			handle_heredoc(cmd, cmd->file->name);
		else if (file->type == OUT)
			cmd->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == APPEND)
			cmd->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cmd->fd = -1;
		if (cmd->fd < 0)
		{
			perror("open file");
			minishell_exit(1, true);
		}
		if (file->type == IN || file->type == HEREDOC)
			dup2(cmd->fd, STDIN_FILENO);
		else
			dup2(cmd->fd, STDOUT_FILENO);
		close(cmd->fd);
		if (file->type == HEREDOC)
			unlink("/tmp/heredoc");
		file = file->next;
	}
}


