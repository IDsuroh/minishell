/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:38:48 by suroh             #+#    #+#             */
/*   Updated: 2025/03/28 20:35:32 by suroh            ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>
# include "./tokenizer.h"
# include "./error_checker.h"
# include "./parser.h"
# include "./executor.h"
# include "./envp.h"

typedef struct s_almighty
{
	t_list_header	*var_list;
	int				exit_stat;
	int				interactive;
	int				pending_fd;
	t_pid_node		*acpl; //active_child_pid_list
}	t_almighty;

// handle_input.c
void	handle_input(t_almighty *mighty, char *input);

// main.c
void	free_all(t_almighty *mighty);

// signals.c
void	terminal_interrupt(t_pid_node *acpl);
void	signalhandler_interactive(int signum);
void	init_signals_interactive(void);
void	init_signals_subshell(void);

#endif
