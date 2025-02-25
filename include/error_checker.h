/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:06:28 by suroh             #+#    #+#             */
/*   Updated: 2025/02/25 00:16:37 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CHECKER_H
# define ERROR_CHECKER_H

# include "tokenizer.h"

// open_input_checker.c
char	*open_input_checker(t_token_node **tokens, bool *op_open,
			char *full_input);

// error_check_flags_1.c
bool	no_preceding_command(t_token_node *token);
bool	consecutive_operators(t_token_node *token, t_token_node *next);
bool	incomplete_input(t_token_node *token, bool *op_open);
bool	error_prompt(t_token_node **tokens, bool *op_open);

// error_check_flags_2.
bool	error_in_new_prompt(t_token_node **tmp_tokens);

#endif
