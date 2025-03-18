/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 07:58:58 by suroh             #+#    #+#             */
/*   Updated: 2025/03/18 17:21:22 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_pwd(t_almighty *boy, char *buff, char *var)
{
	t_var_elm	*elm;

	elm = get_value(boy->var_list, var);
	if (elm)
	{
		free(elm->value);
		elm->value = ft_strdup(buff);
	}
	else
		add_var(boy->var_list, create_var(ft_strdup(var),
				ft_strdup(buff)));
	free(buff);
}

void	free_var_list(t_list_header *header)
{
	t_var_elm	*current;
	t_var_elm	*next;

	current = header->head;
	while (current)
	{
		next = current->next;
		del_var(current);
		current = next;
	}
	free(header);
}

void	free_pid_list(t_pid_node *acpl)
{
	t_pid_node	*tmp;

	while (acpl)
	{
		tmp = acpl;
		acpl = acpl->next;
		free(tmp);
	}
}

void	free_all(t_almighty *mighty)
{
	if (mighty->var_list)
	{
		free_var_list(mighty->var_list);
		mighty->var_list = NULL;
	}
	if (mighty->acpl)
	{
		free_pid_list(mighty->acpl);
		mighty->acpl = NULL;
	}
}

void	free_envp_array(char **envp, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
