/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:38:48 by suroh             #+#    #+#             */
/*   Updated: 2025/03/05 20:02:21 by miteixei         ###   ########.fr       */
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

//extern volatile int	g_signal;

extern int				g_last_exit_status;

typedef struct s_var_elm
{
	char				*key;
	char				*value;
	struct s_var_elm	*prev;
	struct s_var_elm	*next;
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
	t_redir_list	redirections;
	char			*here_doc_str;
}	t_almighty;

// env.c
char			**make_envp(t_list_header *header);
t_var_elm		*extract_var(char *var);
t_var_elm		*get_value(t_list_header *header, char *key);
t_list_header	*init_var_list(char **envp);

// env_expansion.c
void			expand_env_variables(t_list_header *var_list,
					t_token_node **tokens);
// env_expansion_utils.c
char			*get_prefix(const char *str);
char			*get_var_name(const char *dollar_ptr);
char			*get_suffix(const char *dollar_ptr);
int				get_pid_from_proc(void);

// env_utils_1.c
void			print_vars(char **envp);
t_var_elm		*create_var(char *key, char *value);
void			add_var(t_list_header *header, t_var_elm *var);
void			del_var(t_var_elm *var);
void			rem_var(t_list_header *header, t_var_elm *var);

// env_utils_2.c
void			free_var_list(t_list_header *header);

//
void			init_signals(void);
void			terminal_interrupt(void);

#endif
