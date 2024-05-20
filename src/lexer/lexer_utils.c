/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:05 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/17 16:59:00 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//print tokens for a test
void	tokens_print(char **tokenise)
{
	int	i;

	i = -1;
	while (tokenise[++i])
		printf(" [.] %s\n", tokenise[i]);
}

//free array of strings
void	array_free(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
