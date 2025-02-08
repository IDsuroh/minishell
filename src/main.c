/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/02/08 19:10:36 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_input(char *input)
{
	t_op_sequence	*tmp_seq;
	t_token_node	**current;

	if (*input)
		add_history(input);
	current = tokenizer(input);
	printf("\n");
	print_tokens_colors(current);
	printf("\n");
	free(input);
	if (current == NULL)
		return ;
	tmp_seq = parse_tokens(current);
	printf("\n");
	print_parsing(tmp_seq);
	printf("\n");
	free_node_list(current);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	((void)argc, (void)argv);
	(void)envp;
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
		handle_input(input);
	}
	return (0);
}

//		if (exists_error(current))
//		{
//			free_node_list(current);
//			continue ;
//		}
