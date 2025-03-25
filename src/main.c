/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 21:01:17 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_main_struct(t_almighty *mighty, char **envp)
{
	mighty->var_list = init_var_list(envp);
	mighty->exit_stat = 0;
	mighty->interactive = isatty(STDIN_FILENO);
	mighty->acpl = NULL;
	init_signals_interactive();
}

static void	shell_loop(t_almighty *mighty)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (ft_strspn(input, " ") == ft_strlen(input))
		{
			free(input);
			continue ;
		}
		if (*input)
		{
			add_history(input);
			handle_input(mighty, input);
		}
		terminal_interrupt(mighty->acpl);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_almighty	main_struct;

	(void)argc, (void)argv;
	init_main_struct(&main_struct, envp);
	shell_loop(&main_struct);
	free_all(&main_struct);
	return (0);
}
