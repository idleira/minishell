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
void	handle_file_redirection(t_dlist **head)
{
	t_list	*file;

	file = ft_lstnew();
	file->name = (*head)->next->value;
	if ((*head)->type == __RED_IN)
		file->type = IN;
	else if ((*head)->type == __RED_OUT)
		file->type = OUT;
	else if ((*head)->type == __RED_APP)
		file->type = APPEND;
	else if ((*head)->type == __HEREDOC)
		file->type = HEREDOC;
	else
		file->type = NONE;
}

//handles file redirection
// void	handle_file_redirection(t_dlist **head)
// {
// 	t_list	*file;

// 	file = ft_lstnew();
// 	file->name = (*head)->next->value;
// 	if ((*head)->type == __RED_IN)
// 		file->type = IN;
// 	else if ((*head)->type == __RED_OUT)
// 		file->type = OUT;
// 	else if ((*head)->type == __RED_APP)
// 		file->type = APPEND;
// 	else if ((*head)->type == __HEREDOC)
// 		file->type = HEREDOC;
// 	else
// 		file->type = NONE;
// }

void	process_word_tokens(t_dlist **head, char **args)
{
	while (*head && (*head)->type != __PIPE)
	{
		if (((*head)->type == __WORD && !(*head)->prev)
			|| ((*head)->type == __WORD && ((*head)->prev->type == __WORD
					|| (*head)->prev->type == __PIPE)))
		{
			*args = ft_strjoin(*args, (*head)->value);
			*args = ft_strjoin(*args, ft_strdup("\n"));
		}
		else if (((*head)->type == __RED_APP || (*head)->type == __RED_IN
				|| (*head)->type == __HEREDOC || (*head)->type == __RED_OUT))
		{
			handle_file_redirection(head);
		}
		*head = (*head)->next;
	}
}

// parses the lexer list and creates a parser list
void	parse_cmd_list(t_parser **parser, t_dlist *head)
{
	t_parser	*node;
	char		*args;

	while (head)
	{
		node = node_create_pars();
		node->file = NULL;
		args = NULL;
		process_word_tokens(&head, &args);
		if (args)
			node->args = ft_split(args, '\n');
		else
			node->args = NULL;
		node_append_pars(parser, node);
		if (head)
			head = head->next;
	}
}
