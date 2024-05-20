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

#include "../../inc/minishell.h"

static void	trim_numeric(t_parser *parser)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = (void *)0;
	while (parser->tokens[parser->i][i] != '$')
		i++;
	if (i)
		tmp = ft_substr(parser->tokens[parser->i], 0, i);
	tmp2 = parser->tokens[parser->i];
	parser->tokens[parser->i] = ft_substr(parser->tokens[parser->i],
			parser->j + 1,
			ft_strlen(parser->tokens[parser->i]));
	parser->tokens[parser->i] = ft_strjoin(tmp, parser->tokens[parser->i]);
	parser->param_exp = 0;
	free (tmp2);
}

static void	expand_env(t_parser *parser, t_env *env)
{
	char	*tmp;
	char	*tmp2;
	char	*var;
	int		i;

	tmp2 = parser->tokens[parser->i];
	tmp = ft_substr(parser->tokens[parser->i], 0, parser->j - 1);
	i = parser->j;
	while (parser->tokens[parser->i][i]
		&& is_valid(parser->tokens[parser->i][i]))
		++i;
	var = ft_substr(parser->tokens[parser->i], parser->j, i - parser->j);
	if (env_get(var, env))
	{
		parser->tokens[parser->i] = ft_strjoin(tmp,
				ft_strdup(env_get(var, env)));
		parser->tokens[parser->i] = ft_strjoin(parser->tokens[parser->i],
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	}
	else
		parser->tokens[parser->i] = ft_strjoin(tmp,
				ft_substr(tmp2, i, ft_strlen(tmp2)));
	parser->param_exp = 0;
	parser->j = get_index(parser->tokens[parser->i]);
	return (free (var), free (tmp2));
}

void	expand_vars(t_parser *parser, t_env *env)
{
	parser->i = -1;
	while (parser->tokens[++parser->i])
	{
		wildcards_expander(parser);
		parser->j = quotes_skip(parser->tokens[parser->i]);
		parser->param_exp = 0;
		while (parser->tokens[parser->i][++parser->j])
		{
			if (parser->tokens[parser->i][parser->j] == '$')
				parser->param_exp = 1;
			else if (parser->param_exp
				&& (ft_isdigit(parser->tokens[parser->i][parser->j]
					&& parser->tokens[parser->i][parser->j] != '0'))
					&& parser->tokens[parser->i][parser->j - 1] == '$')
				trim_numeric(parser);
			else if (parser->param_exp
				&& (ft_isalpha(parser->tokens[parser->i][parser->j])
				|| ft_strchr("0_", parser->tokens[parser->i][parser->j])))
				expand_env(parser, env);
		}
	}
}
