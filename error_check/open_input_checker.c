/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_input_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:43 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 19:35:37 by suroh            ###   ########.fr       */
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
		free_node_list(tmp_tokens);
		*line = NULL;
		return (2);
	}
	free_node_list(tmp_tokens);
	return (3);
}

static char	*process_input_line(t_token_node ***tokens, bool *op_open,
		char *full_input)
{
	char			*cont_input;
	char			*new_full_input;
	t_token_node	**new_tokens;
	int				status;

	status = get_valid_input(*tokens, &cont_input);
	if (status == 0)
		exit(0);
	if (status == 1)
	{
		free_node_list(*tokens);
		*tokens = tokenizer(full_input);
		return (full_input);
	}
	if (status == 2)
		return (free(full_input), free_node_list(*tokens), NULL);
	new_full_input = ft_strjoin(full_input, cont_input);
	free(full_input);
	full_input = new_full_input;
	free(cont_input);
	new_tokens = tokenizer(full_input);
	free_node_list(*tokens);
	*tokens = new_tokens;
	*op_open = false;
	return (full_input);
}

char	*open_input_checker(t_token_node **tokens, bool *op_open,
		char *full_input)
{
	while (error_prompt(tokens, op_open) && *op_open)
	{
		full_input = process_input_line(&tokens, op_open, full_input);
		if (!full_input)
			return (NULL);
	}
	free_node_list(tokens);
	return (full_input);
}
