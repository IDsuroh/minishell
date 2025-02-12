/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:38:48 by suroh             #+#    #+#             */
/*   Updated: 2025/02/08 19:06:36 by suroh            ###   ########.fr       */
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

extern volatile int	g_signal;

typedef struct s_var_elm
{
	char				*key;
	char				*value;
	struct s_var_list	*prev;
	struct s_var_list	*next;
}	t_var_elm;

typedef struct s_list_header
{
	void	*head;
	void	*tail;
	int		size;
}	t_list_header;

char	*ft_strndup(const char *s, size_t n);

void	init_signals(void);
void	terminal_interrupt(void);

// print_utils_2.c
void	print_tokens_colors(t_token_node **current);
void	print_pipe(t_pipe_sequence *pipe);
void	print_cmd(t_op_sequence *seq);
void	print_parsing(t_op_sequence *tmp_seq);

#endif
