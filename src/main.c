/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/02/18 23:27:54 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token_node	**handle_error(t_token_node **current, char *input)
{
	t_token_node	**new_current;

	input = handle_op_open(input);
	if (input == NULL)
		return (NULL);
	free_node_list(current);
	new_current = tokenizer(input);
	free(input);
	return (new_current);
}

static void	handle_input(char *input)
{
	t_op_sequence	*tmp_seq;
	t_token_node	**current;
	bool			op_open;

	op_open = false;
	current = tokenizer(input);
	if (error_prompt(current, &op_open))
	{
		if (op_open == true)
			current = handle_error(current, input);
		else
		{
			free_node_list(current);
			return ;
		}
	}
	if (current == NULL)
		return ;
	print_tokens_colors(current);
	tmp_seq = parse_tokens(current);
	print_parsing(tmp_seq);
	free_node_list(current);
}

int	main(void)
{
	char	*input;

	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		terminal_interrupt();
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strspn(input, " \t\n\v\f\r") == ft_strlen(input))
		{
			free(input);
			continue ;
		}
		if (*input)
			add_history(input);
		handle_input(input);
	}
	return (0);
}
