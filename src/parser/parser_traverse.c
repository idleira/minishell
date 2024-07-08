/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:04:47 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 16:04:47 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/minishell.h"

// // prints details of a single t_dlist node
// static void	traverse_helper(const t_dlist *temp)
// {
// 	printf("[.] value -> %s\n", temp->value);
// 	if (temp->state == __s_quotes)
// 		printf("[.] state -> IN_SINGLE_QUOTES\n");
// 	else if (temp->state == __d_quotes)
// 		printf("[.] state -> IN_DOUBLE_QUOTES\n");
// 	else
// 		printf("[.] state -> WITHOUT_QUOTES\n");
// 	if (temp->type == __RED_IN)
// 		printf("[.] type -> REDIRECTION_IN\n");
// 	else if (temp->type == __RED_OUT)
// 		printf("[.] type -> REDIRECTION_OUT\n");
// }

// // processes a t_dlist structure
// void	traverse_lexer(const t_dlist *head)
// {
// 	const t_dlist *temp = head;
// 	while (temp)
// 	{
// 		printf("---------------------------------\n");
// 		traverse_helper(temp);
// 		if (temp->type == __RED_APP)
// 			printf("[.] type -> REDIRECTION_APPEND\n");
// 		else if (temp->type == __HEREDOC)
// 			printf("[.] type -> HEREDOC\n");
// 		else if (temp->type == __PIPE)
// 			printf("[.] type -> PIPE\n");
// 		else
// 			printf("[.] type -> WORD\n");
// 		printf("---------------------------------\n");
// 		temp = temp->next;
// 	}
// }

// // processes an array of strings
// void	traverse_scanner(char **scanner)
// {
// 	int i = -1;
// 	while (scanner[++i])
// 		printf(" [.] %s\n", scanner[i]);
// }

// // processes a linked list of t_parser nodes
// void	traverse_parser(const t_parser *head)
// {
// 	printf("----------------------\n");
// 	const t_parser *current = head;
// 	while (current)
// 	{
// 		printf("[.] arguments : \n\t");
// 		if (current->args)
// 		{
// 			int i = -1;
// 			while (current->args[++i])
// 				printf("%s ", current->args[i]);
// 		}
// 		else
// 			printf("no arguments\n");
// 		printf("\n");

// 		printf("[.] files :\n");
// 		const t_list *file = current->file;
// 		if (file)
// 		{
// 			while (file)
// 			{
// 				printf("\nname : %s\n", file->name);
// 				if (file->type == HEREDOC)
// 					printf("\ttype : HEREDOC\n");
// 				else if (file->type == APPEND)
// 					printf("\ttype : RED_APPEND\n");
// 				else if (file->type == IN)
// 					printf("\ttype : RED_IN\n");
// 				else if (file->type == OUT)
// 					printf("\ttype : RED_OUT\n");
// 				file = file->next;
// 			}
// 		}
// 		else
// 			printf("\tno files\n");
// 		printf("----------------------\n");
// 		current = current->next;
// 	}
// }