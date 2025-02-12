/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:38:48 by suroh             #+#    #+#             */
/*   Updated: 2025/01/16 18:18:03 by suroh            ###   ########.fr       */
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
# include "./parsing.h"
# include "./tokenizer.h"

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
#endif
