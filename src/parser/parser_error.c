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
	else
	{
		if (node->state == __s_quotes)
			error->error_type = error_of_single_quotes;
		else
			error->error_type = error_of_double_quotes;
	}
}

// checks if the quotes are closed
int	error_for_quotes(t_dlist *node)
{
	int		i;
	int		c;
	char	q;

	if (node->state == __s_quotes)
		q = '\'';
	else
		q = '\"';
	i = 0;
	c = 0;
	while (node->value[i])
	{
		if (node->value[i] == q)
			c++;
		++i;
	}
	return (c % 2 == 0);
}

// checks for errors in the lexer list
int	check_errors(t_dlist *temp, t_errors *error)
{
	if ((temp->type != __WORD && temp->next && temp->next->type != __WORD)
		|| (temp->type != __WORD && !temp->next))
	{
		assign_error_type(temp, error);
		return (1);
	}
	else
	{
		if (!error_for_quotes(temp))
		{
			assign_error_type(temp, error);
			return (1);
		}
	}
	return (0);
}

// handles the errors in the lexer list
void	ft_error(t_dlist	*head, t_errors *error)
{
	t_dlist	*temp;

	temp = head;
	if (temp->type == __PIPE)
	{
		assign_error_type(temp, error);
		return ;
	}
	while (temp)
	{
		if (check_errors(temp, error))
			return ;
		temp = temp->next;
	}
	error->error_type = no_error;
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
	else if (error->error_type == error_of_double_quotes)
		printf("bash: syntax error: unclosed double quotes\n");
	else if (error->error_type == error_of_single_quotes)
		printf("bash: syntax error: unclosed single quotes\n");
	error->exit_staus = 2;
}
