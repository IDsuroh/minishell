/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:06:28 by suroh             #+#    #+#             */
/*   Updated: 2025/02/11 21:20:33 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CHECKER_H
# define ERROR_CHECKER_H

# include "tokenizer.h"

// error_checker.c
bool	error_prompt(t_token_node **tokens, bool *op_open);

// input_open_check.c
char	*handle_op_open(char *input);

#endif
