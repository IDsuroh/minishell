/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:28:08 by suroh             #+#    #+#             */
/*   Updated: 2025/03/10 17:08:25 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*assemble_expanded(char *prefix, char *env_value, char *suffix)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(prefix, env_value);
	result = ft_strjoin(temp, suffix);
	free(temp);
	return (result);
}

static char	*fetch_env_value(char *var_name, t_list_header *var_list)
{
	t_var_elm	*env_var;

	if (ft_strcmp(var_name, "$") == 0)
		return (get_pid_from_proc());
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_strdup("\t***for now not implemented***\t"));
	env_var = get_value(var_list, var_name);
	if (env_var)
		return (ft_strdup(env_var->value));
	return (ft_strdup(""));
}

static char	*replace_variable(const char *str, t_list_header *var_list)
{
	char	*result;
	char	*prefix;
	char	*var_name;
	char	*env_value;
	char	*suffix;

	if (!ft_strchr(str, '$'))
		return (ft_strdup(str));
	prefix = get_prefix(str);
	var_name = get_var_name(ft_strchr(str, '$'));
	env_value = fetch_env_value(var_name, var_list);
	free(var_name);
	suffix = get_suffix(ft_strchr(str, '$'));
	result = assemble_expanded(prefix, env_value, suffix);
	free(env_value);
	free(prefix);
	free(suffix);
	return (result);
}

static char	*expand_token_value(char *str, t_list_header *var_list)
{
	char	*result;
	char	*temp;

	result = ft_strdup(str);
	temp = NULL;
	while (ft_strchr(result, '$'))
	{
		temp = replace_variable(result, var_list);
		free(result);
		result = temp;
	}
	return (result);
}

void	expand_env_variables(t_list_header *var_list, t_token_node **tokens)
{
	int			i;
	char		*old_value;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i]->type == T_VAR)
		{
			old_value = tokens[i]->token_value;
			tokens[i]->token_value = expand_token_value(old_value, var_list);
			free(old_value);
		}
		else if (tokens[i]->type == T_PID)
		{
			old_value = tokens[i]->token_value;
			tokens[i]->token_value = get_pid_from_proc();
			free(old_value);
		}
		else if (tokens[i]->type == T_XVAR)
		{
			old_value = tokens[i]->token_value;
			tokens[i]->token_value = (ft_strdup("\t***for now not implemented***\t"));
			free(old_value);
		}
	}
}

/*
 * static char	*assemble_expanded(char *prefix, char *env_value, char *suffix)
 * 		Concatenates three parts of a string into one final expanded string.
 *
 *
 * static char	*fetch_env_value(char *var_name, t_list_header *var_list)
 *		Retrieves the value associated with a given environment variable name.
 *
 *		Lookup in the Variable List:
 *			It uses get_value(var_list, var_name) to search
 *			the linked list of environment variables.
 *			If found, it returns the corresponding value;
 *			otherwise, it returns an empty string.
 *
 * 
 * static char	*replace_variable(const char *str, t_list_header *var_list)
 *		Replaces the first occurrence of a variable in the string with
 *		its corresponding value.
 *
 * How It Works:
 *
 *	Locate the Dollar Sign:
 *		It uses ft_strchr to find the first $ in the string.
 *		If none is found, it simply duplicates and returns the string.
 *	Extract Parts Around the Variable:
 *		get_prefix(str) extracts the substring before the variable.
 *		get_var_name(dollar_ptr) extracts the variable name starting at the $.
 *		get_suffix(dollar_ptr) extracts the substring after the variable.
 *	Fetch the Variable’s Value:
 *		Calls fetch_env_value with the extracted variable name and
 *		the variable list.
 *	Reassemble the String:
 *		Finally, assemble_expanded is used to concatenate the prefix,
 *		the fetched value, and the suffix.
 *
 *
 * static char	*expand_token_value(char *str, t_list_header *var_list)
 * 		Fully expands all environment variable references in a token.
 *
 * How It Works:
 *
 * 	Initial Duplication:
 * 		Duplicates the original token string.
 * 	Iterative Replacement:
 * 		In a loop, as long as the result contains a $ character,
 * 		it calls replace_variable to replace the first occurrence.
 * 		The old string is freed and replaced by the new expanded string.
 * 	Return:
 * 		Once no more $ characters are found,
 * 		the fully expanded string is returned.
 *
 * 
 * void	expand_env_variables(t_list_header *var_list, t_token_node **tokens)
 *		Iterates over an array of token nodes and expands
 *		environment variable tokens.
 *
 *
 *
 *
 *
 *
 *
 */
