/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:38:48 by suroh             #+#    #+#             */
/*   Updated: 2025/03/03 18:16:40 by miteixei         ###   ########.fr       */
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
	t_var_elm	*head;
	t_var_elm	*tail;
	int			size;
}	t_list_header;

// all purpose struct, containing all important values
//   or references to other structs or lists
typedef struct s_almighty
{
	t_list_header	*var_list;
	int				exit_stat;
}	t_almighty;

// env.c
void			print_vars(char **envp);
char			**make_envp(t_list_header *header);
t_var_elm		*create_var(char *key, char *value);
void			del_var(t_var_elm *var);
void			rem_var(t_list_header *header, t_var_elm *var);
t_var_elm		*extract_var(char *var);
t_var_elm		*get_value(t_list_header *header, char *key);
t_list_header	*init_var_list(char **envp);

//
void			init_signals(void);
void			terminal_interrupt(void);

#endif
