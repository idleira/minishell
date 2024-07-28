/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:37:19 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/27 17:37:19 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	assign_error_type(t_dlist *node, t_errors *error)
{
	if (node->type == __PIPE)
		error->error_type = error_of_pipeline;
	else if (node->type == __RED_IN)
		error->error_type = error_of_redirection_in;
	else if (node->type == __RED_OUT)
		error->error_type = error_of_redirection_out;
	else if (node->type == __HEREDOC)
		error->error_type = error_of_redirection_heredoc;
	else if (node->type == __RED_APP)
		error->error_type = error_of_redirection_append;
}

int	pipe_start_end(t_shell *minishell)
{
	t_dlist	*lexer;

	lexer = minishell->lexer;
	if (lexer->type == __PIPE)
	{
		if (lexer->next == NULL || lexer->prev == NULL)
		{
			minishell->error->error_type = error_of_pipeline;
			return (1);
		}
	}
	return (0);
}

int	syntax_check(t_dlist *lexer, int op_count,
				bool expecting_word, t_errors *error)
{
	if (expecting_word == true
		&& (lexer->type != __WORD || lexer->next == NULL))
	{
		assign_error_type(lexer, error);
		return (1);
	}
	if (op_count > 1 && lexer->type == __PIPE)
	{
		error->error_type = error_of_pipeline;
		return (1);
	}
	if (lexer->prev && lexer->prev->type == __HEREDOC && lexer->type != __WORD)
	{
		assign_error_type(lexer, error);
		return (1);
	}
	if (op_count >= 3)
	{
		assign_error_type(lexer, error);
		return (1);
	}
	error->error_type = no_error;
	return (0);
}

// handles the errors in the lexer list
void	ft_error(t_shell *minishell)
{
	t_dlist	*lexer;
	int		op_count;
	bool	expecting_word;

	op_count = 0;
	expecting_word = false;
	lexer = minishell->lexer;
	if (pipe_start_end(minishell) == 1)
		return ;
	while (lexer)
	{
		if (lexer->type != __WORD)
			op_count++;
		else
			op_count = 0;
		if (syntax_check(lexer, op_count, expecting_word,
				minishell->error) == 1)
			return ;
		else if (lexer->type != __PIPE && lexer->type != __WORD)
			expecting_word = true;
		else if (expecting_word == true || lexer->type == __PIPE)
			expecting_word = false;
		lexer = lexer->next;
	}
}

// displays the error message
void	error_display(t_errors *error)
{
	if (error->error_type == error_of_pipeline)
		printf("bash: syntax error: unexpected token `|'\n");
	else if (error->error_type == error_of_redirection_heredoc)
		printf("bash: syntax error: unexpected token `<<'\n");
	else if (error->error_type == error_of_redirection_append)
		printf("bash: syntax error: unexpected token `>>'\n");
	else if (error->error_type == error_of_redirection_in)
		printf("bash: syntax error: unexpected token `<'\n");
	else if (error->error_type == error_of_redirection_out)
		printf("bash: syntax error: unexpected token `>'\n");
	error->exit_status = 2;
}
