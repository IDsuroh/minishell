/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:50:29 by suroh             #+#    #+#             */
/*   Updated: 2025/03/30 16:37:50 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_vars(t_list_header *header)
{
	t_var_elm	*curr;
	int			count;

	count = 0;
	curr = header->head;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

static t_var_elm	**convert_var_list_to_array(t_list_header *header)
{
	t_var_elm	**arr;
	t_var_elm	*curr;
	int			count;
	int			i;

	count = count_vars(header);
	arr = ft_calloc(count, sizeof(t_var_elm *));
	if (!arr)
		return (NULL);
	curr = header->head;
	i = 0;
	while (curr)
	{
		arr[i] = curr;
		i++;
		curr = curr->next;
	}
	return (arr);
}

static void	sort_var_array(t_var_elm **arr, int count)
{
	int			i;
	int			j;
	t_var_elm	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(arr[i]->key, arr[j]->key) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_var_array(t_var_elm **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (arr[i]->exported == true)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(arr[i]->key, STDOUT_FILENO);
			if (arr[i]->value != NULL)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(arr[i]->value, STDOUT_FILENO);
				ft_putstr_fd("\"", STDOUT_FILENO);
			}
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		i++;
	}
}

void	print_export_list(t_almighty *mighty)
{
	int			count;
	t_var_elm	**arr;

	count = mighty->var_list->size;
	arr = convert_var_list_to_array(mighty->var_list);
	if (!arr)
		return ;
	sort_var_array(arr, count);
	print_var_array(arr, count);
	free(arr);
}
