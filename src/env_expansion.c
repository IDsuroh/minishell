/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:28:08 by suroh             #+#    #+#             */
/*   Updated: 2025/03/05 23:12:46 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*assemble_expanded(char *prefix, char *env_value, char *suffix)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(prefix, env_value);
	free(prefix);
	free(env_value);
	result = ft_strjoin(temp, suffix);
	free(temp);
	free(suffix);
	return (result);
}

static char	*fetch_env_value(char *var_name, t_list_header *var_list)
{
	t_var_elm	*env_var;

	if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(get_pid_from_proc()));
	if (ft_strcmp(var_name, "?") == 0)
		return ("\t***for now not implemented***\t");
	env_var = get_value(var_list, var_name);
	if (env_var)
		return (env_var->value);
	return ("");
}

static char	*replace_variable(const char *str, t_list_header *var_list)
{
	char	*dollar_ptr;
	char	*prefix;
	char	*var_name;
	char	*env_value;
	char	*suffix;

	dollar_ptr = ft_strchr(str, '$');
	if (!dollar_ptr)
		return (ft_strdup(str));
	prefix = get_prefix(str);
	var_name = get_var_name(dollar_ptr);
	env_value = fetch_env_value(var_name, var_list);
	free(var_name);
	suffix = get_suffix(dollar_ptr);
	return (assemble_expanded(prefix, env_value, suffix));
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
			tokens[i]->token_value = ft_itoa(get_pid_from_proc());
			free(old_value);
		}
	}
}
