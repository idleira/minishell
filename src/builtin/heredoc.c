/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:46:44 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/07/24 12:38:58 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_heredoc(t_parser *cmd, char *end)
{
	cmd->fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fd < 0)
	{
		perror("Heredoc file not opened");
		minishell_exit(1, false);
	}
	get_lines(cmd, end);
	close(cmd->fd);
	cmd->fd = open("/tmp/heredoc", O_RDONLY);
	if (cmd->fd < 0)
	{
		perror("Heredoc is not opened");
		minishell_exit(1, false);
	}
}

void	get_lines(t_parser *cmd, char *end)
{
	char	*line;
	size_t	len;

	while (1)
	{
		line = readline("> ");
		len = ft_strlen(line);
		if ((ft_strncmp(line, end, len) == 0) || !line)
		{
			free(line);
			break ;
		}
		write(cmd->fd, line, len);
		write(cmd->fd, "\n", 1);
		free(line);
	}
}
