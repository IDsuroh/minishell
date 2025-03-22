/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:24:09 by suroh             #+#    #+#             */
/*   Updated: 2025/03/22 00:31:05 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*remove_quotes(char *s)
{
	char	*result;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len < 2)
		return (ft_strdup(s));
	if ((is_quote_closed(s) && is_quote(s[0])))
	{
		result = malloc(len - 1);
		if (!result)
			return (NULL);
		ft_memcpy(result, s + 1, len - 2);
		result[len - 2] = '\0';
		return (result);
	}
	return (ft_strdup(s));
}

static void	process_quote_rem(t_token_node **tokens)
{
	int		i;
	char	*clean;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		clean = remove_quotes(tokens[i]->token_value);
		free(tokens[i]->token_value);
		tokens[i]->token_value = clean;
		i++;
	}
}

t_token_node	**tokenizer(char *input)
{
	t_token_node	**tokens_list;
	char			**token_storage;
	int				token_count;

	token_count = 0;
	token_storage = NULL;
	if (!input || is_whitespace(input))
		return (NULL);
	token_count = count_tokens(input);
	token_storage = tokenize_input(input, token_count);
	tokens_list = create_node_list(token_storage, token_count);
	process_quote_rem(tokens_list);
	token_count = 0;
	return (tokens_list);
}

/*
 * where the inputs become tokens
 * it will return a double pointer to the structure t_token_node
 * which will look like this:
 *
 * 		typedef struct s_token_node
 * 		{
 * 		t_token_type		type;
 *		char				*token_value;
 *		}	t_token_node;
 *
 *	It is not a linked list. The double pointer is set simple in the purpose
 *	to easily iterate later using ints with while loops.
 *
 *	The token_count is important because it will work as our iterator later
 *	when we have to put types and values in the double pointed lists.
 *
 *	So first we count how many tokens there should be,
 *	then store the tokens as an array of strings,
 *	then after we create the double pointed lists using those two assets.
 *
 *			*files to check:
 *				./tokenizer_counter.c
 *				./tokenize_input.c
 *				./create_node_list.c
 *
 */
