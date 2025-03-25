/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:28:08 by suroh             #+#    #+#             */
/*   Updated: 2025/03/25 20:59:24 by suroh            ###   ########.fr       */
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

static char	*fetch_env_value(char *var_name, t_almighty *mighty)
{
	t_var_elm	*env_var;

	if (ft_strcmp(var_name, "$") == 0)
		return (get_pid_from_proc());
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(mighty->exit_stat));
	env_var = get_value(mighty->var_list, var_name);
	if (env_var)
		return (ft_strdup(env_var->value));
	else
		return (ft_strdup("$"));
}

static char	*replace_variable(const char *str, t_almighty *mighty)
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
	env_value = fetch_env_value(var_name, mighty);
	free(var_name);
	suffix = get_suffix(ft_strchr(str, '$'));
	result = assemble_expanded(prefix, env_value, suffix);
	free(env_value);
	free(prefix);
	free(suffix);
	return (result);
}

static char	*expand_token_value(char *str, t_almighty *mighty)
{
	char	*result;
	char	*temp;

	result = strip_var_quotes(str);
	if (!result)
		return (NULL);
	while (ft_strchr(result, '$'))
	{
		temp = replace_variable(result, mighty);
		if (ft_strcmp(temp, result) == 0)
		{
			free(temp);
			break ;
		}
		free(result);
		result = temp;
	}
	return (result);
}

void	expand_env_variables(t_almighty *mighty, t_token_node **tokens)
{
	int		i;
	char	*old_value;
	char	*tmp;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i]->type == T_VAR || tokens[i]->type == T_PID
			|| tokens[i]->type == T_XVAR)
		{
			old_value = tokens[i]->token_value;
			if (tokens[i]->type == T_VAR)
				tokens[i]->token_value = expand_token_value(old_value, mighty);
			else if (tokens[i]->type == T_PID)
				tokens[i]->token_value = get_pid_from_proc();
			else if (tokens[i]->type == T_XVAR)
			{
				tmp = ft_itoa(mighty->exit_stat);
				tokens[i]->token_value = ft_strjoin(tmp, old_value + 2);
				free(tmp);
			}
			free(old_value);
		}
	}
}
