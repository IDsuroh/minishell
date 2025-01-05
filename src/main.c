/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/01/05 00:01:00 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;

	(void)envp;
	argc = 0;
	argv = NULL;
	while (1)
	{
		init_shell(&shell);
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			ft_token_init(&shell, &argc);
			argv = (char **)malloc(sizeof(char *) * (argc + 1));
			if (argv == NULL)
				return (-1);
			populate_argv(&shell, argv);
			ft_argv_printf(argv);
			ft_free_all(shell,argv);
		}
		free(input);
	}
	return (0);
}
