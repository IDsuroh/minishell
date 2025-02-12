/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:08:11 by suroh             #+#    #+#             */
/*   Updated: 2025/01/30 21:09:21 by suroh            ###   ########.fr       */
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

// counters_helpers.c
void			quote_counter(char **input, int *count);
void			separator_counter(char **input, int *count);
void			var_counter(char **input, int *count);
void			fake_var_counter(char **input, int *count);
void			string_counter(char **input, int *count);

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
char			*store_fake_var(char *token_start, char *token_end,
					char **saveptr);
char			*store_string(char *token_start, char *token_end,
					char **saveptr);

// env_storage_helper.c
char			*tmp_fake_var(char *token_start, char **token_end);
int				fake_var_len(char *tmp);
char			*epur_fake_var(char *token, char *tmp);

// tokenizer_helpers.c
char			*ft_strndup(const char *s, size_t n);
void			free_tokens(char **token_storage);
void			free_node_list(t_token_node **node_list);

// tokenizer_flags_1.c
bool			is_quote(char c);
bool			is_separator(char c);
bool			is_delimiter(char c);
bool			is_string(char c);
bool			is_whitespace(const char *input);

// tokenizer_flags_2.c
bool			is_same_char(char c1, char c2);
bool			is_var(char *c);
bool			is_fake_var(char *c);

// create_node_list.c
t_token_node	**create_node_list(char **token_storage, int token_count);

#endif
