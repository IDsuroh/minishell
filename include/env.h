/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:23:11 by suroh             #+#    #+#             */
/*   Updated: 2025/03/08 19:30:34 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "./tokenizer.h"

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

#endif
