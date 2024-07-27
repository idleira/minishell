/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:41:39 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/07/27 14:30:09 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*expand_no_value(char *token, int start_var, int end_var)
{
	int		token_len;
	char	*new_token;

	token_len = ft_strlen(token) - (end_var - start_var + 1);
	new_token = (char *)ft_malloc(sizeof(char) * (token_len + 1));
	if (!new_token)
		return (NULL);
	ft_strlcpy(new_token, token, start_var - 1);
	ft_strlcat(new_token, token + end_var, token_len + 1);
	ft_free(token);
	return (new_token);
}

static char	*expand_with_value(char	*var_value, char *token,
								int start_var, int end_var)
{
	int		token_len;
	char	*new_token;

	token_len = ft_strlen(token) - (end_var - start_var) + ft_strlen(var_value);
	new_token = (char *)ft_malloc(sizeof(char) * (token_len + 1));
	if (!new_token)
		return (NULL);
	ft_strlcpy(new_token, token, start_var);
	ft_strlcat(new_token, var_value, token_len + 1);
	ft_strlcat(new_token, token + end_var, token_len + 1);
	ft_free(token);
	return (new_token);
}

static char	*expand_var_name(char *token, int start_var, int end_var)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_substr(token, start_var, end_var - start_var);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var_name);
	ft_free(var_name);
	if (!var_value)
		return (expand_no_value(token, start_var, end_var));
	else
		return (expand_with_value(var_value, token, start_var, end_var));
}

char	*expand_var(char *token)
{
	int	i;
	int	start_var;

	i = 0;
	while (token[i])
	{
		if (token[i] != '$')
			i++;
		else
		{
			i++;
			if (token[i] == '?')
			{
				i++;
				continue ;
			}
			start_var = i;
			while ((ft_isalnum(token[i]) || token[i] == '_') && token[i])
				i++;
			token = expand_var_name(token, start_var, i);
			i = start_var - 1;
		}
	}
	return (token);
}
