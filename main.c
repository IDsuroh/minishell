/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/01/02 00:19:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	char	*token;
	char	*delim;
	char	**argv;
	int		i;
	int		argc;

	argv = NULL;
	token = NULL;
	delim = " \t\n";
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
			argv = (char **)malloc(sizeof(char *) * (ft_strlen(input) + 1));
			if (!argv)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			token = ft_strtok(input, delim);
			argc = 0;
			while (token != NULL)
			{
				argv[argc] = token;
				token = ft_strtok(NULL, delim);
				argc++;
			}
			argv[argc] = NULL;
			i = 0;
			while (i < argc)
			{
				printf("argv[%d]: %s\n", i, argv[i]);
				i++;
			}
			printf("argv[%d]: %s\n", i, argv[i]);
			free(argv);
		}
		free(input);
	}
	return (0);
}
