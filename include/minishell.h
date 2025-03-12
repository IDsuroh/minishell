/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:38:48 by suroh             #+#    #+#             */
/*   Updated: 2025/03/11 18:58:52 by suroh            ###   ########.fr       */
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

// all purpose struct, containing all important values
//   or references to other structs or lists
typedef struct s_almighty
{
	t_list_header	*var_list;
	int				exit_stat;
	t_redir			redirections;
	char			*here_doc_str;
	t_pid_node		*active_child_pid_list;
}	t_almighty;

//
void			init_signals(void);

// signals.c
void			terminal_interrupt(pid_t *children_pid);
void			signalhandler_interactive(int signum);
void			init_signals_interactive(void);
void			init_signals_subshell(void);

#endif
