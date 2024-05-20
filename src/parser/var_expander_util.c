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

int	get_index(char *token)
{
	int	i;

	i = 0;
	while (token[i] && !ft_strchr("$\'", token[i]))
		i++;
	return (--i);
}

int	is_valid(char c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

int	quotes_skip(char *string)
{
	int	i;

	i = 0;
	if (string[i] == '\'')
	{
		i++;
		while (string[i] && string[i] != '\'')
			i++;
	}
	return (i - 1);
}
