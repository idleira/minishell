/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:59:10 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/04/22 18:08:26 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	quotes_count(char *str, char qoutes)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == qoutes)
			quote++;
		i++;
	}
	return (quote);
}

int quotes_skip(char *str)
{
	int	i;
	char c;
	
	i = 1;
	c = str[0];
	while(str[i])
	{
		if (str[i] == c)
			return (i);
		else
			i++;
	}
	perror("no clothing quotes c\n");
	return (0);
}

int	check_quotes(char *str)
{
	int	double_qs;
	int	single_qs;

	double_qs = quotes_count(str, '"');
	single_qs = quotes_count(str, '\'');
	if (double_qs == 0 && single_qs == 0)
		return (1);
	if ((ft_strchr(str, '"') && double_qs % 2 == 0)
		|| (ft_strchr(str, '\'') && single_qs % 2 == 0))
		return(1);
	else
		return(0);
}

char *whitespaces_replace(char *str)
{
	int		i;

	i = 0;
	if ((ft_strchr(str, '"') && (quotes_count(str, '"') % 2 == 0))
		|| (ft_strchr(str, '\'') && (quotes_count(str, '"') % 2 == 0)))
	if (check_quotes(str))
	{
		while(str[i])
		{
			if(str[i] == '"' || str[i] == '\'')
			{
				i += quotes_skip(str + i);
					i++;
			}
			if (str[i] == ' ')
			if (str[i] == ' ' || str[i] == '\t')
				str[i] = 26;
			i++;
		}
	}
	else
		return ("the quotes are not closed properly\n");
	return (str);
}

int	char_count(char *str, char c)
{
	int	i;
	int	c;
	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			i += quotes_skip(str + i);
		if (str[i] == c)
			c++;
		i++;
	}
	return(c);
}

void	node_new_add(t_lexer **root, t_lexer *new)
{
	t_lexer	*atm;

	atm = *root;
	while(atm->next)
		atm = atm->next;
	atm->next = new;
}

int	commands_count(char **str)
{
	int	i;

	i = 0;
	while (str[i] && str[i][0] != '|')
	{
		printf("str in count cmd is %s\n", str[i]);
		i++;
	}
	return (i);
}

t_lexer	*new_node(char **str)
{
	int	i;
	int cmd_count; 
	t_lexer	*node;

	i = -1;
	cmd_count = commands_count(str);
	printf("cmd count =  %d\n", cmd_count);
	node = malloc(sizeof(t_lexer));
	node->cmd = malloc(sizeof(char *) * cmd_count + 1);
	while(++i < cmd_count)
	{
		node->cmd[i] = ft_strdup(str[i]);
		if (node->cmd[i] == NULL)
			return (NULL);
		printf("new_node->cmd[%d] %s\n", i, node->cmd[i]);
	}
	node->cmd[cmd_count] = NULL;
	if (str[i] && str[i][0] == '|')
	{
		node->token = ft_strdup(str[i]);
		printf("token added %s\n", node->token);
		if (node->token == NULL)
			return(NULL);
	}
	else
	{
		node->token = NULL;
		printf("token added (null)\n");
	}
	node->next = NULL;
	return (node);
}

t_lexer	*lexer_init_list(char **str)
{
	int	i;
	t_lexer *root;
	t_lexer *node;

	i = 0;
	root = new_node(str + i);
	while(str[i][0] != '|' && str[i])
		i++;
	while(str[i++])
	{
		node = new_node(str + i);
		if (node == NULL)
			return (NULL);
		node_new_add(&root, node);
		i += commands_count(str + i);

	}
	return (root);
}

void	lexer(t_lexer *input)
{
	int i;
	int j;
	char **split_str;

	i = 0;
	j = 0;
	input->original = whitespaces_replace(input->original);
	split_str = ft_split(input->original, 26);
	input = lexer_init_list(split_str);
	j = 0;
	while (input)
	{
		i = 0;
		while (input->cmd[i])
		{
			printf("cmd[%d] of %d note is : %s\n", i, j, input->cmd[i]);
			i++;
		}
		printf("token of %d note is : %s\n", j ,  input->token);
		j++;
		input = input->next;
	}
}
