/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:10:10 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 16:10:10 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// ft_frees scanner resources
void	scanner_ft_free(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		ft_free(tokens[i]);
	ft_free(tokens);
}
