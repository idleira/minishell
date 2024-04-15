/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 17:29:05 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/15 17:33:44 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

void	skip_space(char *input, int *j)
{
	int	i;

	i = *j;
	while (input[i] && is_space(input[i]))
		i++;
	*j = i;
}

void	skip_quotes(int *i, char *input)
{
	int	quote;

	quote = input[*i];
	(*i) = (*i) + 1;
	while (input[*i] && input[*i] != quote)
		(*i) = (*i) + 1;
	if (input[*i] && input[*i] == quote)
		(*i) = (*i) + 1;
}
