/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   parser.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/27 17:43:07 by ibeliaie		  #+#	#+#			 */
/*   Updated: 2024/05/27 17:43:07 by ibeliaie		 ###   ########.fr	   */
/*																			*/
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

void	process_word_tokens(t_dlist **lexer, t_parser *node,  char **args)
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
			file = handle_file_redirection(lexer);
			ft_lstadd_back(&node->file, file);
		}
		*lexer = (*lexer)->next;
	}
}


void	remove_quotes(t_dlist **lexer)
{
	t_dlist	*node;
	char	*new_value;
	int		i;
	int		j;
	char	quote;

	quote = '\0';
	node = *lexer;
	while (node)
	{
		i = 0;
		j = 0;
		new_value = malloc(ft_strlen((*lexer)->value) + 1);
		if (!new_value)
			return ;
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
		free(node->value);
		node->value = new_value;
		node = node->next;
	}
}
// parses the lexer list and creates a parser list
void	parse_cmd_list(t_parser **parser, t_dlist *lexer)
{
	t_parser	*node;
	char		*args;

	remove_quotes(&lexer);
	while (lexer)
	{
		node = node_create_pars();
		node->file = NULL;
		args = NULL;
		process_word_tokens(&lexer, node, &args);
		if (args)
			node->args = ft_split(args, '\n');
		else
			node->args = NULL;
		node_append_pars(parser, node);
		if (lexer)
			lexer = lexer->next;
	}
}
