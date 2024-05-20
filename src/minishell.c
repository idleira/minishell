/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:12:37 by ibeliaie          #+#    #+#             */
/*   Updated: 2024/05/20 15:12:37 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h "

int	main(int argc, char **argv, char **envp)
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_prompt	*prompt;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = NULL;
	env = env_list_create(env, envp);
	while (1)
	{
		lexer = (t_lexer *)malloc(sizeof(t_lexer));
		prompt = (t_prompt *)malloc(sizeof(t_prompt));
		parser = (t_parser *)malloc(sizeof(t_parser));
		lexer->cmd = get_input(prompt);
		if (ft_strlen(lexer->cmd))
		{
			parser->tokens = tokenise(lexer);
			if (lexer->error == 1)
				ft_putendl_fd("[!] syntax error: unclosed quotation mark", 1);
			else if (lexer->error == 2)
				ft_putendl_fd("[!] parsing error : unexpected symbol encountered", 1);
			else
			{
                quotes_process(parser);
				input_process(parser->tokens2);
				array_free(parser->tokens);
				array_free(parser->tokens2);
			}
		}
		free_pointers(lexer, prompt, parser);
	}
	return (0);
}