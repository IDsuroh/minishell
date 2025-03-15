/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:38:48 by suroh             #+#    #+#             */
/*   Updated: 2025/03/15 20:07:03 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>
# include "./tokenizer.h"
# include "./error_checker.h"
# include "./parser.h"
# include "./executor.h"
# include "./env.h"

//extern volatile int	g_signal;

typedef struct s_almighty
{
	t_list_header	*var_list; //to dynamically update for built-ins
	int				exit_stat;
	t_redir			redirections;
	t_pid_node		*acpl; //active_child_pid_list
	char			**envp; //to handle external commands (execve)
}	t_almighty;

//
void	init_signals(void);

// signals.c
void	terminal_interrupt(t_pid_node *acpl);
void	signalhandler_interactive(int signum);
void	init_signals_interactive(void);
void	init_signals_subshell(void);

#endif

/*
 * 	var_list is an internal linked list that holds environment variables,
 * 	allowing dynamic updates by built-in commands like export, unset, or cd.
 *
 * 	In contrast, envp is a standard char ** array that external commands
 * 	require via execve. Storing envp separately provides immediate,
 * 	efficient access to the environment without having to rebuild it
 * 	from var_list each time.
 *
 */
