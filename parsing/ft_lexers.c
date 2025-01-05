/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 19:08:53 by suroh             #+#    #+#             */
/*   Updated: 2025/01/05 21:58:53 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parsing.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*input = NULL;
	char		*token_start;
	char		*token_end;

	if (str != NULL)
		input = str;
	if (input == NULL)
		return (NULL);
	token_start = input;
	while (*token_start && ft_strchr(delim, *token_start))
		token_start++;
	if (*token_start == '\0')
		return (input = NULL);
	token_end = token_start;
	while (*token_end && !ft_strchr(delim, *token_end))
		token_end++;
	if (*token_end == '\0')
		input = NULL;
	else
	{
		*token_end = '\0';
		input = token_end + 1;
	}
	return (token_start);
}

void	init_shell(t_shell *shell, char *input)
{
	shell->cmd = ft_strdup(input);
	shell->delim = " \t\n";
	shell->token = NULL;
}

int	ft_strtok_count(char *str, char *delim)
{
	int		count;
	char	*tmp;
	char	*token;

	count = 0;
	tmp = ft_strdup(str);
	token = ft_strtok(tmp, delim);
	while (token != NULL)
	{
		count++;
		token = ft_strtok(NULL, delim);
	}
	free(tmp);
	return (count);
}

void	ft_token_init(t_shell *shell)
{
	int	argc;
	int	count;

	argc = 0;
	count = ft_strtok_count(shell->cmd, shell->delim);
	shell->token = (char **)malloc(sizeof(char *) * (count + 1));
	if (shell->token == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	shell->token[argc] = ft_strtok(shell->cmd, shell->delim);
	while (argc < count)
	{
		printf("token: %s\n", shell->token[argc]);
		argc++;
		shell->token[argc] = ft_strtok(NULL, shell->delim);
	}
	printf("token: %s\n", shell->token[argc]);
	printf("argc count: %d\n", argc);
}

void	ft_init_lex(t_shell *shell, char *input)
{
	init_shell(shell, input);
	ft_token_init(shell);
}
