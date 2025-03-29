/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/03/29 18:45:14 by miteixei         ###   ########.fr       */
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
		init_signals_interactive();
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!*input || ft_strspn(input, " ") == ft_strlen(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		init_signals_execution();
		terminal_interrupt(mighty);
		mighty->input = input;
		handle_input(mighty, input);
		mighty->input = NULL;
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
	if (mighty->tokens)
		free_node_list(mighty->tokens);
	if (mighty->tmp_seq)
		free_op_sequence(mighty->tmp_seq);
	if (mighty->input)
		free(mighty->input);
	rl_clear_history();
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
