/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_open_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:43 by suroh             #+#    #+#             */
/*   Updated: 2025/02/11 21:27:58 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*prompt_opener(t_token_node **tokens)
{
	t_token_node	*last;
	int				i;

	i = 0;
	while (tokens[i])
	{
		last = tokens[i];
		i++;
	}
	if (last == NULL)
		return ("minishell$ ");
	if (last->type == T_PIPE)
		return ("pipe> ");
	if (last->type == T_AND)
		return ("cmdand> ");
	if (last->type == T_OR)
		return ("cmdor> ");
	return ("minishell$ ");
}

static char	*open_input_checker(t_token_node **tokens, bool *op_open,
								char *full_input)
{
	char	*prompt;
	char	*cont_input;
	char	*new_full_input;

	while (error_prompt(tokens, op_open) && *op_open)
	{
		prompt = prompt_opener(tokens);
		cont_input = readline(prompt);
		if (cont_input == NULL)
		{
			printf("exit\n");
			break ;
		}
		new_full_input = ft_strjoin(full_input, cont_input);
		free(full_input);
		full_input = new_full_input;
		free(cont_input);
		free_node_list(tokens);
		tokens = tokenizer(full_input);
		op_open = false;
	}
	free_node_list(tokens);
	return (full_input);
}

char	*handle_op_open(char *input)
{
	t_token_node	**tokens;
	char			*full_input;
	bool			op_open;

	full_input = ft_strdup(input);
	free(input);
	tokens = tokenizer(full_input);
	full_input = open_input_checker(tokens, &op_open, full_input);
	return (full_input);
}
