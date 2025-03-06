/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:43:24 by suroh             #+#    #+#             */
/*   Updated: 2025/03/06 21:01:47 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*extract_token(char *token_start, char *token_end, char **saveptr)
{
	char	*token;

	if ((is_quote(*token_start) && is_quote_closed(token_start))
		|| (is_var_squote(token_start) || is_var_dquote(token_start)))
		token = store_quote(token_start, token_end, saveptr);
	else if (is_separator(*token_start))
		token = store_separator(token_start, token_end, saveptr);
	else if (is_var(token_start))
		token = store_var(token_start, token_end, saveptr);
	else
		token = store_string(token_start, token_end, saveptr);
	return (token);
}

char	*ft_strtok_r(char *str, char **saveptr)
{
	char	*token_start;
	char	*token_end;
	char	*token;

	if (str != NULL)
		*saveptr = str;
	while (*saveptr && **saveptr && is_delimiter(**saveptr))
		(*saveptr)++;
	if (*saveptr == NULL || **saveptr == '\0')
		return (NULL);
	token_start = *saveptr;
	token_end = token_start;
	token = extract_token(token_start, token_end, saveptr);
	if (token == NULL)
		return (NULL);
	if (*saveptr && **saveptr == '\0')
		*saveptr = NULL;
	return (token);
}

char	**tokenize_input(char *input, int token_count)
{
	char	**token_storage;
	char	*token;
	char	*saveptr;
	int		i;

	saveptr = NULL;
	token_storage = ft_calloc(token_count + 1, sizeof(char *));
	if (!token_storage)
		return (NULL);
	i = 0;
	token = ft_strtok_r(input, &saveptr);
	while (token != NULL && i < token_count)
	{
		token_storage[i] = token;
		token = ft_strtok_r(NULL, &saveptr);
		i++;
	}
	token_storage[i] = NULL;
	free(token);
	return (token_storage);
}

/*
 * The most important part of the tokenizer.
 * 
 * static char	*extract_token(char *token_start, char *token_end,
 * 															char **saveptr)
 * Purpose:
 * 		A helper function which determines what kind of token is present
 * 		at the current position of the input and then delegates the creation
 * 		of that token to the appropriate storage function.
 *
 * 		- almost identical with the counter logic.
 *
 * char	*ft_strtok_r(char *str, char **saveptr)
 * Purpose:
 * 		A reentrant tokenizer, similar to the standard strtok_r, which splits
 * 		the input string into tokens based on delimiters.
 *
 *		 - If a new string (str) is provided, it resets the tokenization state
 *			by setting *saveptr to the beginning of the string.
 *		 - It advances the saveptr past any leading delimiter characters
 *			(as determined by is_delimiter), so that tokenization starts
 *			at the first non-delimiter.
 *		 - If the end of the string is reached (either saveptr is NULL
 *		 	or points to the null terminator), it returns NULL to signal
 *		 	that there are no more tokens.
 *		 - The function sets token_start (and initially token_end) to
 *		 	the current position and then calls extract_token to process
 *		 	and extract the next token.
 *		 - After token extraction, if the saveptr points to the end of
 *		 	the string (i.e., the next character is the null terminator),
 *		 	it sets *saveptr to NULL to mark that tokenization is complete.
 *
 * char	**tokenize_input(char *input, int token_count)
 * Purpose:
 * 		This function tokenizes the entire input string and stores all the tokens
 * 		in an array. The number of tokens expected is given by token_count.
 *
 * 		 - It allocates an array of pointers (token_storage) that will hold up
 * 		 	to token_count tokens, plus one extra slot for a terminating
 * 		 	NULL pointer.
 * 		 - It initializes the tokenization process by calling ft_strtok_r
 * 		 	with the input string and a saveptr variable.
 * 		 - In a loop, as long as tokens are returned and the index is less than
 * 		 	the token_count, it stores each token in the array.
 * 		 - For subsequent calls, ft_strtok_r is passed NULL so it continues
 * 		 	tokenizing from where it left off since the saveptr variable
 * 		 	remembers the position of where the function left off.
 *
 * 				*next file to check:
 * 				./tokenizer_flags_1.c
 * 				./tokenizer_flags_2.c
 * 				./tokenizer_flags_3.c
 * 				./storage_logic.c
 */
