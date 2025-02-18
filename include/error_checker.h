/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:06:28 by suroh             #+#    #+#             */
/*   Updated: 2025/02/15 16:27:04 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CHECKER_H
# define ERROR_CHECKER_H

# include "tokenizer.h"

// error_checker.c
bool	no_preceding_command(t_token_node *token);
bool	consecutive_operators(t_token_node *token, t_token_node *next);
bool	incomplete_input(t_token_node *token, bool *op_open);
bool	error_prompt(t_token_node **tokens, bool *op_open);

// input_open_check.c
char	*handle_op_open(char *input);

// error_check_flags.c
bool	char_is_whitespace(char c);

#endif
