/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:12:31 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 18:51:05 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_export_no_equal(t_almighty *mighty, char *arg)
{
	t_var_elm	*node;
	t_var_elm	*new_node;
	char		*key;

	node = get_value(mighty->var_list, arg);
	if (node)
		node->exported = true;
	else
	{
		key = ft_strdup(arg);
		new_node = create_var(key, NULL);
		if (new_node)
			new_node->exported = true;
		add_var(mighty->var_list, new_node);
	}
}

void	builtin_export(t_almighty *mighty, char **args)
{
	int	i;

	mighty->exit_stat = 0;
	if (args[1] == NULL)
	{
		print_export_list(mighty);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_input(args[i]))
			print_export_error(args[i], mighty);
		else if (ft_strchr(args[i], '='))
			_export(mighty, args[i]);
		else
			handle_export_no_equal(mighty, args[i]);
		i++;
	}
}

static void	update_existing_export(t_var_elm *node, char *key, char *value)
{
	free(node->value);
	node->value = value;
	node->exported = true;
	free(key);
}

static void	add_new_export(t_almighty *mighty, char *key, char *value)
{
	t_var_elm	*new_node;

	new_node = create_var(key, value);
	if (new_node)
		new_node->exported = true;
	add_var(mighty->var_list, new_node);
}

void	_export(t_almighty *mighty, char *var)
{
	char		*key;
	char		*value;
	t_var_elm	*node;

	if (!var)
		return ;
	if (!is_valid_input(var))
	{
		print_export_error(var, mighty);
		return ;
	}
	parse_export_var(var, &key, &value);
	node = get_value(mighty->var_list, key);
	if (node != NULL)
		update_existing_export(node, key, value);
	else
		add_new_export(mighty, key, value);
}
