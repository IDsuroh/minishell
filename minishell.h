/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:38:48 by suroh             #+#    #+#             */
/*   Updated: 2025/01/02 21:13:37 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>

volatile int	g_signal = 0;

typedef struct s_shell
{
	char	*cmd;
	char	*cmd_cpy;
	char	*token;
	char	*delim;
	size_t	n;
}	t_shell;

void	ft_free_all(t_shell shell, char **argv);
void	ft_token_init(t_shell *shell, int *argc);
void	populate_argv(t_shell *shell, char **argv);
void	ft_argv_printf(char **argv);

char	*ft_strtok(char *str, const char *delim);

//maybe we need this function
//ssize_t	ft_getline(char **lineptr, size_t *n, int fd);

#endif
