/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/03/28 20:33:25 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_main_struct(t_almighty *mighty, char **envp)
{
	mighty->var_list = init_var_list(envp);
	mighty->exit_stat = 0;
	mighty->interactive = isatty(STDIN_FILENO);
	mighty->pending_fd = -1;
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
		if (!*input || ft_strspn(input, " ") == ft_strlen(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		handle_input(mighty, input);
		terminal_interrupt(mighty->acpl);
		free(input);
	}
}

void	free_all(t_almighty *mighty)
{
	if (mighty->var_list)
	{
		free_var_list(mighty->var_list);
		mighty->var_list = NULL;
	}
	if (mighty->acpl)
	{
		free_pid_list(mighty->acpl);
		mighty->acpl = NULL;
	}
	if (mighty->pending_fd != -1)
	{
		close(mighty->pending_fd);
		mighty->pending_fd = -1;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_almighty	*main_struct;

	(void)argc, (void)argv;
	main_struct = ft_calloc(1, sizeof(t_almighty));
	if (!main_struct)
	{
		perror("ft_calloc");
		exit(EXIT_FAILURE);
	}
	init_main_struct(main_struct, envp);
	shell_loop(main_struct);
	free_all(main_struct);
	free(main_struct);
	return (0);
}
