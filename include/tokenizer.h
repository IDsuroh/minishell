/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:08:11 by suroh             #+#    #+#             */
/*   Updated: 2025/03/05 22:43:56 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stddef.h>

typedef enum e_token_type
{
	T_NONE,
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_AND,
	T_OR,
	T_VAR,
	T_XVAR,
	T_PID,
}	t_token_type;

typedef struct s_token_node
{
	t_token_type		type;
	char				*token_value;
}	t_token_node;

// tokenizer.c
t_token_node	**tokenizer(char *input);

// tokenizer_counters.c
int				count_tokens(char *input);

<<<<<<< HEAD
=======
// tokenizer_complex_var.c

>>>>>>> 46edab62e58d218bd892f0de625c2e7bfa64b521
// tokenizer_utils.c
char			*ft_strtok_r(char *str, char **saveptr);
char			**tokenize_input(char *input, int token_count);

// storing_logic.c
char			*store_quote(char *token_start, char *token_end,
					char **saveptr);
char			*store_separator(char *token_start, char *token_end,
					char **saveptr);
char			*store_var(char *token_start, char *token_end,
					char **saveptr);
char			*store_string(char *token_start, char *token_end,
					char **saveptr);

// storage_logic_helper.c
void			handle_short_var(char **token_end, int *i);
void			handle_normal_var(char **token_end, int *i);

// tokenizer_helpers.c
char			*ft_strndup(const char *s, size_t n);
void			free_tokens(char **token_storage);
void			free_node_list(t_token_node **node_list);
void			free_incomp_node_list(t_token_node **token_list, int allocated);
void			free_node_list_no_values(t_token_node **node_list);

// tokenizer_flags_1.c
bool			is_quote(char c);
bool			is_separator(char c);
bool			is_delimiter(char c);
bool			is_string(char c);
bool			is_whitespace(char *input);

// tokenizer_flags_2.c
bool			is_same_char(char c1, char c2);
bool			is_var(char *c);
bool			char_is_whitespace(char c);
bool			is_quote_closed(char *p);

// tokenizer_flags_3.c
bool			is_var_squote(char *c);
bool			is_var_dquote(char *c);

// create_node_list.c
t_token_node	**create_node_list(char **token_storage, int token_count);

#endif
