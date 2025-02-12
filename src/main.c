/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/02/11 21:42:36 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		{
			input = handle_op_open(input);
			free_node_list(current);
			current = tokenizer(input);
		}
	}
	print_tokens_colors(current);
	free(input);
	if (current == NULL)
		return ;
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
