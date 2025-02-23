/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/02/23 20:17:42 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token_node	**handle_error(char *input)
{
	t_token_node	**new_current;

	input = handle_op_open(input);
	if (input == NULL)
		return (NULL);
	new_current = tokenizer(input);
	free(input);
	return (new_current);
}

static t_token_node	**duplicate(t_token_node **tokens)
{
	int				i;
	int				count;
	t_token_node	**copy;

	count = 0;
	while (tokens[count])
		count++;
	copy = (t_token_node **)malloc(sizeof(t_token_node *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = tokens[i];
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	process_tokens(t_token_node **tokens)
{
	t_op_sequence	*tmp_seq;
	t_token_node	**tokens_dup;
	int				i;

	print_tokens_colors(tokens);
	tokens_dup = duplicate(tokens);
	if (!tokens_dup)
	{
		free_node_list(tokens);
		return ;
	}
	tmp_seq = parse_tokens(tokens_dup);
	free(tokens_dup);
	print_parsing(tmp_seq);
//	i = -1;
//	while (tokens[++i])
//		printf("%s\t", tokens[i]->token_value);
	free_op_sequence(tmp_seq);
	i = -1;
	while (tokens[++i])
		tokens[i]->token_value = NULL;
	free_node_list_no_values(tokens);
}

static void	handle_input(char *input)
{
	t_token_node	**tokens;
	bool			op_open;

	op_open = false;
	tokens = tokenizer(input);
	if (error_prompt(tokens, &op_open))
	{
		if (op_open == true)
		{
			free_node_list(tokens);
			tokens = handle_error(input);
			if (!tokens)
				return ;
		}
		else
		{
			free_node_list(tokens);
			return ;
		}
	}
	process_tokens(tokens);
}

int	main(void)
{
	char	*input;

	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		terminal_interrupt();
		if (!input)
			break ;
		if (input && ft_strspn(input, " ") == ft_strlen(input))
		{
			free(input);
			continue ;
		}
		if (*input)
		{
			add_history(input);
			handle_input(input);
		}
	}
	return (0);
}

/* When each token’s token_value is set to NULL,
 * it is basically telling that there's nothing to free for that field.
 * In this case, the parser’s free functions
 * (like free_argv, free_pipeline, free_op_sequence) have
 * already freed the memory that token_value pointed to.
 * However, the free_node_list function still iterates over each token and
 * calls free on token_value.
 * Since calling free(NULL) is safe (it does nothing),
 * setting token_value to NULL prevents a double-free.
 * The free_node_list(tokens) at the end is necessary because of the
 * functionality itself and also because of memory that is not directly
 * accessible in the handle_input or main or etc. functions.
 * */
