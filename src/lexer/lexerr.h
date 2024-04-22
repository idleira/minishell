/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:09:50 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/22 18:10:52 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef struct	s_lexer
{
	char	**cmd;
	char	*token;
	char	*original;
	struct s_lexer	*next;
}   t_lexer;

typedef struct	s_envp
{
	char **env;
}   t_envp;

void	lexer(t_lexer *input);
#endif