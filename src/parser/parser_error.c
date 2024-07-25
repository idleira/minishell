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

// assigns the error type to the error struct
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

// checks for errors in the lexer list
int	check_errors(t_dlist *lexer, t_errors *error)
{
	if ((lexer->type != __WORD && lexer->next && lexer->next->type != __WORD)
		|| (lexer->type != __WORD && !lexer->next))
	{
		assign_error_type(lexer, error);
		return (1);
	}
	return (0);
}

// handles the errors in the lexer list
void	ft_error(t_shell *minishell)
{
	t_dlist	*lexer;

	lexer = minishell->lexer;
	if (lexer->type == __PIPE)
	{
		assign_error_type(lexer, minishell->error);
		return ;
	}
	while (lexer)
	{
		if (check_errors(lexer, minishell->error))
			return ;
		lexer = lexer->next;
	}
	minishell->error->error_type = no_error;
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
