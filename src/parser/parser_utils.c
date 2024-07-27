/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:44:35 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/27 17:44:35 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//handles file redirection
t_list	*handle_file_redirection(t_dlist **lexer)
{
	t_list	*file;

	file = ft_lstnew();
	file->name = (*lexer)->next->value;
	if ((*lexer)->type == __RED_IN)
		file->type = IN;
	else if ((*lexer)->type == __RED_OUT)
		file->type = OUT;
	else if ((*lexer)->type == __RED_APP)
		file->type = APPEND;
	else if ((*lexer)->type == __HEREDOC)
		file->type = HEREDOC;
	else
		file->type = NONE;
	return (file);
}

static void	vibe_check(char **args, t_dlist **lexer)
{
	if ((*lexer)->type == __HEREDOC)
	{
		*args = ft_strjoin(*args, "<< ");
		*args = ft_strjoin(*args, ft_strdup("\n"));
	}
	else
	{
		if (!(*lexer)->prev)
			*args = ft_strjoin(*args, "help\n");
	}
}

// processes the word tokens in the lexer list and creates a parser node
void	process_word_tokens(t_dlist **lexer, t_parser *node, char **args)
{
	t_list	*file;

	while (*lexer && (*lexer)->type != __PIPE)
	{
		if (((*lexer)->type == __WORD && !(*lexer)->prev)
			|| ((*lexer)->type == __WORD && ((*lexer)->prev->type == __WORD
					|| (*lexer)->prev->type == __PIPE)))
		{
			*args = ft_strjoin(*args, (*lexer)->value);
			*args = ft_strjoin(*args, ft_strdup("\n"));
		}
		else if (((*lexer)->type == __RED_APP || (*lexer)->type == __RED_IN
				|| (*lexer)->type == __HEREDOC || (*lexer)->type == __RED_OUT))
		{
			vibe_check(args, lexer);
			file = handle_file_redirection(lexer);
			ft_lstadd_back(&node->file, file);
		}
		*lexer = (*lexer)->next;
	}
}

// removes quotes from the lexer list values and returns the new value
char	*process_node(t_dlist *node, char *new_value)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = '\0';
	while (node->value[i])
	{
		if ((node->value[i] == '\'' && quote != '\"')
			|| (node->value[i] == '\"' && quote != '\''))
		{
			if (quote == '\0')
				quote = node->value[i];
			else if (quote == node->value[i])
				quote = '\0';
		}
		else
			new_value[j++] = node->value[i];
		i++;
	}
	new_value[j] = '\0';
	return (new_value);
}

// removes quotes from the lexer list values and updates the lexer list
void	remove_quotes(t_dlist **lexer)
{
	char	*new_value;
	t_dlist	*node;

	node = *lexer;
	while (node)
	{
		new_value = ft_malloc(ft_strlen(node->value) + 1);
		if (!new_value)
			return ;
		new_value = process_node(node, new_value);
		ft_free(node->value);
		node->value = new_value;
		node = node->next;
	}
}
