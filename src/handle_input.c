/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:14:37 by suroh             #+#    #+#             */
/*   Updated: 2025/03/28 20:33:59 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/colors.h"

static t_token_node	**handle_error_input(char *input)
{
	t_token_node	**tokens;
	bool			op_open;

	op_open = false;
	tokens = tokenizer(input);
	input = open_input_checker(tokens, &op_open, input);
	if (input == NULL)
		return (NULL);
	tokens = tokenizer(input);
	free(input);
	return (tokens);
}

static t_token_node	**duplicate(t_token_node **tokens)
{
	int				idx;
	int				count;
	t_token_node	**copy;

	count = 0;
	while (tokens[count])
		count++;
	copy = (t_token_node **)malloc(sizeof(t_token_node *) * (count + 1));
	if (!copy)
		return (NULL);
	idx = 0;
	while (idx < count)
	{
		copy[idx] = malloc(sizeof(t_token_node));
		copy[idx]->token_value = ft_strdup(tokens[idx]->token_value);
		if (!copy[idx] || !copy[idx]->token_value)
		{
			free_incomp_node_list(copy, idx);
			return (NULL);
		}
		copy[idx]->type = tokens[idx]->type;
		idx++;
	}
	copy[idx] = NULL;
	return (copy);
}

static void	process_tokens(t_almighty *mighty, t_token_node **tokens)
{
	t_op_sequence	*tmp_seq;
	t_token_node	**tokens_dup;

	tokens_dup = duplicate(tokens);
	if (!tokens_dup)
		return (free_node_list(tokens), (void)0);
	tmp_seq = parse_tokens(tokens_dup);
	free_node_list(tokens_dup);
	mighty->tokens = tokens;
	mighty->tmp_seq = tmp_seq;
	execute_parsed_structure(tmp_seq, mighty);
	mighty->tokens = NULL;
	mighty->tmp_seq = NULL;
	free_op_sequence(tmp_seq);
	free_node_list(tokens);
}

void	handle_input(t_almighty *mighty, char *input)
{
	t_token_node	**tokens;
	bool			op_open;

	op_open = false;
	tokens = tokenizer(input);
	expand_env_variables(mighty, tokens);
	if (error_prompt(tokens, &op_open))
	{
		if (op_open == true)
		{
			free_node_list(tokens);
			tokens = handle_error_input(input);
			if (!tokens)
				return ;
		}
		else
		{
			free_node_list(tokens);
			return ;
		}
	}
	process_tokens(mighty, tokens);
}

/*static void	process_tokens(t_almighty *mighty, t_token_node **tokens)
{
	t_op_sequence	*tmp_seq;
	t_token_node	**tokens_dup;

	print_tokens_colors(tokens);
	tokens_dup = duplicate(tokens);
	if (!tokens_dup)
		return (free_node_list(tokens), (void)0);
	tmp_seq = parse_tokens(tokens_dup);
	free_node_list(tokens_dup);
	print_parsing(tmp_seq);
	execute_parsed_structure(tmp_seq, mighty);
	free_op_sequence(tmp_seq);
	free_node_list(tokens);
}*/
