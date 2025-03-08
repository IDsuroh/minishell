/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_input_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:21:43 by suroh             #+#    #+#             */
/*   Updated: 2025/03/08 18:55:15 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*prompt_opener(t_token_node **tokens)
{
	t_token_node	*last;
	int				i;

	i = 0;
	while (tokens[i])
	{
		last = tokens[i];
		i++;
	}
	if (last == NULL)
		return ("minishell$ ");
	if (last->type == T_PIPE)
		return ("pipe> ");
	if (last->type == T_AND)
		return ("cmdand> ");
	if (last->type == T_OR)
		return ("cmdor> ");
	return ("minishell$ ");
}

static int	get_valid_input(t_token_node **tokens, char **line)
{
	t_token_node	**tmp_tokens;

	*line = readline(prompt_opener(tokens));
	if (*line == NULL)
	{
		printf("minishell: syntax error: unexpected end of file\nexit\n");
		return (0);
	}
	if (ft_strspn(*line, " \t\n\v\f\r") == ft_strlen(*line))
	{
		free(*line);
		*line = NULL;
		return (1);
	}
	tmp_tokens = tokenizer(*line);
	if (error_in_new_prompt(tmp_tokens))
	{
		free(*line);
		free_node_list(tmp_tokens);
		*line = NULL;
		return (2);
	}
	free_node_list(tmp_tokens);
	return (3);
}

static char	*process_input_line(t_token_node ***tokens, bool *op_open,
		char *full_input)
{
	char			*cont_input;
	char			*new_full_input;
	t_token_node	**new_tokens;
	int				status;

	status = get_valid_input(*tokens, &cont_input);
	if (status == 0)
		exit(0);
	if (status == 1)
	{
		free_node_list(*tokens);
		*tokens = tokenizer(full_input);
		return (full_input);
	}
	if (status == 2)
		return (free(full_input), free_node_list(*tokens), NULL);
	new_full_input = ft_strjoin(full_input, cont_input);
	free(full_input);
	full_input = new_full_input;
	free(cont_input);
	new_tokens = tokenizer(full_input);
	free_node_list(*tokens);
	*tokens = new_tokens;
	*op_open = false;
	return (full_input);
}

char	*open_input_checker(t_token_node **tokens, bool *op_open,
		char *full_input)
{
	while (error_prompt(tokens, op_open) && *op_open)
	{
		full_input = process_input_line(&tokens, op_open, full_input);
		if (!full_input)
			return (NULL);
	}
	free_node_list(tokens);
	return (full_input);
}

/*
 * static char	*prompt_opener(t_token_node **tokens)
 * Purpose:
 * 		Chooses the appropriate prompt string based on
 * 		the last token from the previous input.
 *
 *
 * static int	get_valid_input(t_token_node **tokens, char **line)
 * Purpose:
 * 		Reads a new line of input from the user using a prompt
 * 		determined by the current tokens, and performs basic validation
 * 		on that input.
 *
 * How It Works:
 *	
 *	Prompting:
 *		Calls readline with the prompt provided by prompt_opener(tokens).
 *	Handling EOF:
 *		If readline returns NULL (user pressed Ctrl+D), it prints
 *		an error message for an unexpected end of file and returns status 0.
 *	Checking for Empty Input:
 *		Uses ft_strspn to check if the input contains only whitespace.
 *		If so, it frees the input and returns status 1.
 *	Syntax Check:
 *		Tokenizes the input line and checks it for syntax errors
 *		(using error_in_new_prompt). If there’s a syntax error, it frees
 *		the allocated memory and returns status 2.
 *	Valid Input:
 *		If the input passes these checks, it frees the temporary token list
 *		and returns status 3 indicating valid input.
 *
 *
 * static char	*process_input_line(t_token_node ***tokens, bool *op_open,
 * 		char *full_input)
 * Purpose:
 * 		When the command input is incomplete
 * 		(for example, ending with a pipe or logical operator),
 * 		this function prompts the user for an additional line and
 * 		concatenates it to the existing input.
 *
 * How It Works:
 *
 * 	Obtain Additional Input:
 * 		Calls get_valid_input to read another line of input.
 * 	Based on the returned status:
 * 		Status 0: EOF encountered; the program exits.
 * 		Status 1: Input is empty (only whitespace).
 * 			It re-tokenizes the existing full input and
 * 			returns it without change.
 * 		Status 2: A syntax error was detected;
 * 			the function frees the full input and tokens, then returns NULL.
 *  Concatenate Input:
 *  	For valid additional input (status 3), it concatenates
 *  	the new input to the current full_input using ft_strjoin.
 *  Update Tokens:
 *  	The tokens are re-generated (by tokenizing the new full input),
 *  	and the open operator flag (op_open) is reset to false.
 *  Return Updated Input:
 *  	The updated full input is returned.
 *
 *
 * char	*open_input_checker(t_token_node **tokens, bool *op_open,
 * 		char *full_input)
 * Purpose:
 * 		Continually checks whether the input (already tokenized)
 * 		has syntax errors that suggest it is incomplete
 * 		(for example, if it ends with an operator).
 * 		If so, it repeatedly prompts the user for more input
 * 		until the command is complete.
 *
 * How It Works:
 * 	Loop for Incomplete Input:
 * 		Enters a loop that continues as long as error_prompt(tokens, op_open)
 * 		returns true and the open operator flag (*op_open) is set.
 * 		This indicates that there is a syntax error caused by
 * 		an operator expecting a following command.
 * 	Process Additional Lines:
 * 		Calls process_input_line to get more input, concatenates it to
 * 		the existing command (full_input), and updates the token list.
 * 		If process_input_line returns NULL
 * 		(for example, due to a syntax error in the additional input or an EOF),
 * 		the function returns NULL.
 * 	Cleanup and Return:
 * 		Once the input no longer indicates an incomplete command,
 * 		it frees the token list and returns the complete input string.
 */
