/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:08:11 by suroh             #+#    #+#             */
/*   Updated: 2025/01/12 23:45:19 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stddef.h>

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_AND,
	T_OR,
	T_VAR,
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

// tokenizer_utils.c
char			*ft_strtok_r(char *str, char **saveptr);
char			**tokenize_input(char *input, int token_count);

// tokenizer_helpers.c
char			*ft_strndup(const char *s, size_t n);
void			free_tokens(char **token_storage);
void			free_node_list(t_token_node **node_list);

// tokenizer_flags.c
bool			is_quote(char c);
bool			is_separator(char c);
bool			is_delimiter(char c);
bool			is_string(char c);

// create_node_list.c
t_token_node	**create_node_list(char **token_storage, int token_count);

#endif
