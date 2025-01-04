/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 23:24:37 by suroh             #+#    #+#             */
/*   Updated: 2025/01/01 23:50:42 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	init_shell(t_shell *shell)
{
	shell->cmd = NULL;
	shell->cmd_cpy = NULL;
	shell->token = NULL;
	shell->delim = " \n";
	shell->n = 0;
	write (STDOUT_FILENO, "$ ", 2);
}*/

/*int	custom_main(void)
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
}*/

int	main(void)
{
	char	*cmd;
	char	*cmd_cpy;
	char	*token;
	char	*delim;
	size_t	n;
	int		i;
	int		argc;
	char	**argv;

	cmd = NULL;
	cmd_cpy = NULL;
	token = NULL;
	delim = " \n";
	argc = 0;
	argv = NULL;
	n = 0;
	write (STDOUT_FILENO, "$ ", 2);
	if (ft_getline(&cmd, &n, STDIN_FILENO) == -1)
		return (-1);
	cmd_cpy = ft_strdup(cmd);
	token = ft_strtok(cmd, delim);
	while (token != NULL)
	{
		token = ft_strtok(NULL, delim);
		argc++;
	}
	printf("argc count: %d\n", argc);
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (-1);
	token = ft_strtok(cmd_cpy, delim);
	i = 0;
	while (token != NULL)
	{
		argv[i] = token;
		token = ft_strtok(NULL, delim);
		i++;
	}
	argv[i] = NULL;
	i = -1;
	while (argv[++i] != NULL)
		printf("argv[%d]: %s\n", i, argv[i]);
	printf("argv[%d]: %s\n", i, argv[i]);
	free(cmd);
	free(cmd_cpy);
	free(argv);
	return (0);
}
