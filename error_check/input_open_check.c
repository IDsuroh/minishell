/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_open_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:43 by suroh             #+#    #+#             */
/*   Updated: 2025/02/16 22:41:01 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	error_in_new_prompt(t_token_node **tmp_tokens)
{
	int	i;

	if (no_preceding_command(tmp_tokens[0]))
		return (true);
	i = 0;
	while (tmp_tokens[i])
	{
		if (tmp_tokens[i + 1] && consecutive_operators(tmp_tokens[i],
				tmp_tokens[i + 1]))
			return (true);
		i++;
	}
	return (false);
}

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

static int	get_valid_input(t_token_node **tokens, char **line)
{
	t_token_node	**tmp_tokens;

	*line = readline(prompt_opener(tokens));
	if (*line == NULL)
	{
		printf("minishell: syntax error: unexpected end of file\nexit\n");
		return (0);
	}
	if (ft_strspn(*line, " \t\n\v\f\r") == ft_strlen(*line))
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	tmp_tokens = tokenizer(*line);
	if (error_in_new_prompt(tmp_tokens))
	{
		free(*line);
		*line = NULL;
		free_node_list(tmp_tokens);
		return (2);
	}
	free_node_list(tmp_tokens);
	return (3);
}

static char	*open_input_checker(t_token_node **tokens, bool *op_open,
								char *full_input)
{
	char	*cont_input;
	char	*new_full_input;
	int		status;

	while (error_prompt(tokens, op_open) && *op_open)
	{
		status = get_valid_input(tokens, &cont_input);
		if (status == 0)
			exit(0);
		if (status == 1)
			continue ;
		if (status == 2)
		{
			free(full_input);
			return (NULL);
		}
		new_full_input = ft_strjoin(full_input, cont_input);
		free(full_input);
		full_input = new_full_input;
		free(cont_input);
		tokens = tokenizer(full_input);
		*op_open = false;
	}
	free_node_list(tokens);
	return (full_input);
}

char	*handle_op_open(char *input)
{
	t_token_node	**tokens;
	bool			op_open;

	op_open = false;
	tokens = tokenizer(input);
	input = open_input_checker(tokens, &op_open, input);
	if (input == NULL)
		return (NULL);
	free_node_list(tokens);
	return (input);
}
