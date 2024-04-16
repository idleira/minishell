/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:54:18 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/16 16:56:16 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_command(char *input)
{
    // implement command parsing
}

static void	parse_arguments(char *input)
{
    // implement argument parsing
}

void		parse_input(char *input)
{
    parse_command(input);
    parse_arguments(input);
}