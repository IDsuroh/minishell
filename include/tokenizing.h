/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 23:08:11 by suroh             #+#    #+#             */
/*   Updated: 2025/01/10 15:27:42 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

# include <stddef.h>

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_OP_PAR,
	T_CL_PAR,
	T_AND,
	T_OR,
}	t_token_type;

typedef struct s_token_node
{
	struct s_token_node	*next;
	struct s_token_node	*prev;
	t_token_type		type;
	char				*token_value;
}	t_token_node;

//ft_tokenizer.c
void			ft_token_start(t_token_node *token_list);
void			ft_init_node(t_token_node **current, t_token_node *token_list);
void			ft_link_token(t_token_node *token_node, char **tmp, int *count);
t_token_node	*ft_token_init(char *line, int *token_count);
t_token_node	*ft_tokenizer(char *input);

//ft_token_utils.c
char			*ft_strtok(char *str, const char *delim);
int				ft_strtok_count(char *str, char *delim);

//ft_token_utils_2.c
bool			ft_is_quote(char c);
bool			ft_is_separator(char c);
char			*ft_store_quote(char *token_start, char **input);
void			ft_free_token_list(t_token_node *token_list);
char			*ft_store_separator(char *token_start, char **input);

//ft_token_utils_3.c
char			*ft_strndup(const char *s, size_t n);
#endif
