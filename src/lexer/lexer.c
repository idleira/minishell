/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:04:11 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/18 18:23:40 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//handles parts of the input string that are enclosed in quotes
int	quotes_check(t_lexer *lexer, char *s)
{
    lexer->j = lexer->i++;
    while (s[lexer->i] != lexer->quote && s[lexer->i])
        lexer->i++;
    if (s[lexer->i])
        lexer->line = ft_strjoin(lexer->line, ft_substr(s, lexer->j,
                                                         lexer->i - lexer->j + 1));
    else
        return (1);
    return (0);
}

//formats special operator sequences with new lines for clarity
int	operators_separate(t_lexer *lexer, char *s)
{
    if (!ft_memcmp(s + lexer->i, ">>>", 3)
        || !ft_memcmp(s + lexer->i, "<<<", 3)
        || !ft_memcmp(s + lexer->i, "&&&", 3)
        || !ft_memcmp(s + lexer->i, "|||", 3))
        return (2);
    else if (!ft_memcmp(s + lexer->i, ">>", 2)
             || !ft_memcmp(s + lexer->i, "<<", 2)
             || !ft_memcmp(s + lexer->i, "||", 2)
             || !ft_memcmp(s + lexer->i, "&&", 2))
    {
        lexer->line = ft_strjoin(lexer->line, ft_strdup("\n"));
        lexer->line = ft_strjoin(lexer->line, ft_substr(s, lexer->i, 2));
        lexer->line = ft_strjoin(lexer->line, ft_strdup("\n"));
        lexer->i++;
    }
    else
    {
        lexer->line = ft_strjoin(lexer->line, ft_strdup("\n"));
        lexer->line = ft_strjoin(lexer->line, ft_substr(s, lexer->i, 1));
        lexer->line = ft_strjoin(lexer->line, ft_strdup("\n"));
    }
    return (0);
}

//loops through the string, processing each character and handling it accordingly
int	input_process(char *s, t_lexer *lexer)
{
    while (s[lexer->i])
    {
        if (s[lexer->i] == '\"' || s[lexer->i] == '\'')
        {
            lexer->quote = s[lexer->i];
            if (quotes_check(lexer, s))
                return (1);
        }
        else if (ft_strchr("<>|&", s[lexer->i]))
        {
            if (operators_separate(lexer, s))
                return (2);
        }
        else if (ft_strchr(" \t\n\v\f\r", s[lexer->i]))
            lexer->line = ft_strjoin(lexer->line, ft_strdup("\n"));
        else
            lexer->line = ft_strjoin(lexer->line, ft_substr(s, lexer->i, 1));
        lexer->i++;
    }
    return (0);
}

//tokenizes the input string and returns an array of tokens
char	**tokenise(t_lexer *lexer)
{
    lexer->i = 0;
    lexer->line = NULL;
    lexer->error = input_process(lexer->cmd, lexer);
    if (lexer->error)
        return (free(lexer->line), (void *)0);
    else
    {
        lexer->tokens = ft_split(lexer->line, '\n');
        free(lexer->line);
    }
    return (lexer->tokens);
}
