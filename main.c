/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:25:58 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/02 17:07:19 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexing(t_tokens *tokens, char *input)
{
	int	i;

	if (*input)
		printf("%s\n", input);
	else
		printf("input: %s", input);
	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '<' || input[i] == '>')
			extract_file(tokens, &input[i], i);
		i++;
		// else
		// 	extract_word(&input[i]);
	}
}

int	main(int ac, char **env)
{
	(void)ac;
	(void)env;
	t_tokens *tokens;
	tokens = ft_memset(&tokens, 0, sizeof(tokens));
	char *input = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		add_history(input);
		lexing(tokens, input);
	}
	free(input);
}