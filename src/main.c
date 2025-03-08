/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/03/08 21:02:25 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/colors.h"

static t_token_node	**handle_error_input(char *input)
{
	t_token_node	**tokens;
	bool			op_open;

	op_open = false;
	tokens = tokenizer(input);
	input = open_input_checker(tokens, &op_open, input);
	if (input == NULL)
		return (NULL);
	tokens = tokenizer(input);
	free(input);
	return (tokens);
}

static t_token_node	**duplicate(t_token_node **tokens)
{
	int				idx;
	int				count;
	t_token_node	**copy;

	count = 0;
	while (tokens[count])
		count++;
	copy = (t_token_node **)malloc(sizeof(t_token_node *) * (count + 1));
	if (!copy)
		return (NULL);
	idx = 0;
	while (idx < count)
	{
		copy[idx] = malloc(sizeof(t_token_node));
		copy[idx]->token_value = ft_strdup(tokens[idx]->token_value);
		if (!copy[idx] || !copy[idx]->token_value)
		{
			free_incomp_node_list(copy, idx);
			return (NULL);
		}
		copy[idx]->type = tokens[idx]->type;
		idx++;
	}
	copy[idx] = NULL;
	return (copy);
}

static void	process_tokens(t_token_node **tokens)
{
	t_op_sequence	*tmp_seq;
	t_token_node	**tokens_dup;

	tokens_dup = duplicate(tokens);
	if (!tokens_dup)
		return (free_node_list(tokens), (void)0);
	tmp_seq = parse_tokens(tokens_dup);
	free_node_list(tokens_dup);
	print_parsing(tmp_seq);
	free_op_sequence(tmp_seq);
	free_node_list(tokens);
}

static void	handle_input(t_list_header *var_list, char *input)
{
	t_token_node	**tokens;
	bool			op_open;

	op_open = false;
	tokens = tokenizer(input);
	if (error_prompt(tokens, &op_open))
	{
		if (op_open == true)
		{
			free_node_list(tokens);
			tokens = handle_error_input(input);
			if (!tokens)
				return ;
		}
		else
		{
			free_node_list(tokens);
			return ;
		}
	}
	expand_env_variables(var_list, tokens);
	print_tokens_colors(tokens);
	process_tokens(tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_almighty	main_struct;

	(void)argc, (void)argv;
//	init_signals();
	main_struct.var_list = init_var_list(envp);
	while (1)
	{
		input = readline("minishell$ ");
//		terminal_interrupt();
		if (!input)
			break ;
		if (input && ft_strspn(input, " ") == ft_strlen(input))
		{
			free(input);
			continue ;
		}
		if (*input)
		{
			add_history(input);
			handle_input(main_struct.var_list, input);
		}
	}
	free_var_list(main_struct.var_list);
	return (0);
}

/* 
 * static t_token_node	**handle_error_input(char *input)
 * Purpose:
 * 		This function is used when the initial tokenization of
 * 		the user input has detected an error—often related to
 * 		open operators such as '|', '||', '&&'.
 *
 * 		 - starts by converting raw input strings into tokens
 * 		 - this function is only called when the op_open flag in the
 * 		 	handle_input function is true.
 * 		 - it returns the new tokens array.
 * 		 This function leads to the error checking process which
 * 		 is done after the tokenizing or after it goes through the
 * 		 lexer.
 *
 * 		 * next file to check for this function:
 * 		 	./../error_check/open_input_checker.c
 *
 *
 * static t_token_node	**duplicate(t_token_node **tokens)
 * Purpose:
 * 		This function creates a duplicate (deep copy) of an array of token nodes.
 * 		Solely to properly and safely free the tokenized assets after parsing.
 *
 * 		* next function to check for this function:
 *			static void	process_tokens(t_token_node **tokens)
 *
 * 
 * static void	process_tokens(t_token_node **tokens)
 * Purpose:
 * 		This function handles the further processing of the tokens after
 * 		initial validation and error-checking.
 *
 * 		 - where the printing of the tokens and the parsed tokens happen.
 * 		
 * 		* next function to check for this function:
 * 			static void	handle_input(t_list_header *var_list, char *input)
 *
 * 		* next file to check after tokenization:
 * 			./../parser/parser.c
 *
 *
 * static void	handle_input(t_list_header *var_list, char *input)
 * Purpose:
 * 		This is the primary function that handles a user’s input string
 * 		in the shell. It coordinates tokenization, error checking,
 * 		environment variable expansion, and processing of tokens.
 *
 *		 - the bool op_open is to check if there are open inputs.
 *
 *		* next functions and files to check for this function:
 *			./../include/minishell.h
 *			./../include/tokenizer.h
 *			./../include/parser.h
 *			./../tokenizer/tokenizer.c
 *			./../error_check/error_check_flags_1.c
 *			./env_expansion.c
 *			**for printing:
 *			./print_utils_1.c
 *			./print_utils_2.c
 *
 *
 * int	main:
 * 	classic int main that run the program.
 * 	init_var_list(envp);
 * 	a structure that contains the information of the system's envp.
 *
 * the parsing and the error checking in the handle_input function.
 */
