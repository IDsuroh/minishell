/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/01/05 21:57:42 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

int	main(void)
{
	t_shell	shell;
	char	*input;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			ft_init_lex(&shell, input);
		}
		free(input);
	}
	return (0);
}
