/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:24:37 by suroh             #+#    #+#             */
/*   Updated: 2024/12/29 20:56:01 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell)
{
	shell->cmd = NULL;
	shell->cmd_cpy = NULL;
	shell->token = NULL;
	shell->delim = " \n";
	shell->n = 0;
	write (STDOUT_FILENO, "$ ", 2);
}

int	main(void)
{
	t_shell	shell;
	int		argc;
	char	**argv;

	argc = 0;
	argv = NULL;
	init_shell(&shell);
	if (ft_getline(&shell.cmd, &shell.n, STDIN_FILENO) == -1)
		return (-1);
	ft_token_init(&shell, &argc);
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (-1);
	populate_argv(&shell, argv);
	ft_argv_printf(argv);
	ft_free_all(shell, argv);
	return (0);
}
