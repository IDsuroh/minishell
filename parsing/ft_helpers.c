/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:08:53 by suroh             #+#    #+#             */
/*   Updated: 2025/01/04 23:41:19 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

void	init_shell(t_shell *shell)
{
	shell->cmd = NULL;
	shell->cmd_cpy = NULL;
	shell->token = NULL;
	shell->delim = " \t\n";
}

void	ft_free_all(t_shell shell, char **argv)
{
	free(shell.cmd);
	free(shell.cmd_cpy);
	free(argv);
}

void	ft_token_init(t_shell *shell, int *argc)
{
	*argc = 0;
	shell->cmd_cpy = ft_strdup(shell->cmd);
	shell->token = ft_strtok(shell->cmd, shell->delim);
	while (shell->token != NULL)
	{
		(*argc)++;
		shell->token = ft_strtok(NULL, shell->delim);
	}
	printf("argc count: %d\n", *argc);
}

void	populate_argv(t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	shell->token = ft_strtok(shell->cmd_cpy, shell->delim);
	while (shell->token != NULL)
	{
		argv[i++] = shell->token;
		shell->token = ft_strtok(NULL, shell->delim);
	}
	argv[i] = NULL;
}

void	ft_argv_printf(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	printf("argv[%d]: %s\n", i, argv[i]);
}
