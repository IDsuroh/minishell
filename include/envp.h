/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:23:11 by suroh             #+#    #+#             */
/*   Updated: 2025/03/27 22:22:26 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include "./tokenizer.h"
# include "./executor.h"

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

// envp.c
char			**make_envp(t_list_header *header);
t_var_elm		*extract_var(char *var);
t_var_elm		*get_value(t_list_header *header, char *key);
t_list_header	*init_var_list(char **envp);

// envp_expansion.c
void			expand_env_variables(t_almighty *mighty, t_token_node **tokens);

// envp_expansion_utils_1.c
char			*get_prefix(const char *str);
char			*get_var_name(const char *dollar_ptr);
char			*get_suffix(const char *dollar_ptr);
char			*extract_pid_from_stat(const char *stat_str);
char			*get_pid_from_proc(void);

// envp_expansion_utils_2.c
int				get_var_len(const char *var_start);
char			*get_special_var_name(const char *var_start);
char			*get_normal_var_name(const char *var_start);
char			*strip_var_quotes(char *str);

// envp_utils_1.c
void			print_vars(char **envp);
t_var_elm		*create_var(char *key, char *value);
void			add_var(t_list_header *header, t_var_elm *var);
void			del_var(t_var_elm *var);
void			rem_var(t_list_header *header, t_var_elm *var);

// envp_utils_2.c
void			free_var_list(t_list_header *header);
void			free_envp_array(char **envp, size_t count);

// envp_utils_3.c
void			insert_new_var(t_list_header *header, t_var_elm *var);
void			update_existing_var(t_var_elm *existing, t_var_elm *new_var);

#endif
