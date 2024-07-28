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
