/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:30:50 by suroh             #+#    #+#             */
/*   Updated: 2025/02/22 21:12:09 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_token_node my_node(void)
{
	static t_token_node node;

	return (&node);
}
{
	my_node()->token_value = NULL;
	my_node()->type = T_IDENTIFIER;
	my_node()->next = NULL;
}
static void mark_pipes(char **s)
{
	int i;
	int c;

	i = -1;
	c = 0;
	while ((*s)[++i])
	{
		if (((*s)[i] == '"' || (*s)[i] == '\'') && !c)
			c = (*s)[i];
		else if ((*s)[i] == c)
			c = 0;
		else if ((*s)[i] == '|' && !c)
			(*s)[i] = 2;

	}
}
static void print_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		printf("matrix[%d]: %s\n", i, matrix[i]);
		i++;
	}
}


static int pipes_count(char *input)
{
	int i;
	int c;

	i = -1;
	c = 0;
	while (input[++i])
	{
		if (input[i] == 2)
			c++;
	}
	return (c);
}

static int matrix_size(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

static int matrix_check(char **matrix)
{
	int i;

	i = -1;
	while (matrix[++i])
	{
		if (!*matrix[i])
			return (1);
	}
	return (0);
}

static void take_rediret(char **cmd)
{
	int i;
	int c;

	i = -1;
	c = 0;
	while ((*cmd)[++i])
	{
		if ((*cmd)[i] == '"' || (*cmd)[i] == '\'')
			c = (*cmd)[i];
		else if ((*cmd)[i] == '>' && !c)
		{
			if ((*cmd)[i + 1] == '>')
				(*cmd)[i] = 3;
			else
				(*cmd)[i] = 1;
		}
		else if ((*cmd)[i] == '<' && !c)
			(*cmd)[i] = 2;
	}
}

static void take_redirec(t_cmd **cmd)
{

	if (!check_redirect((*cmd)->cmd))
		take_rediret(&(*cmd)->cmd);



}
static char **matrix (char *input)
{
	char **matrix;

	mark_pipes(&input);
	matrix = ft_split(input, 2);
	print_matrix(matrix);
	if (matrix_size(matrix) <= pipes_count(input) + 1)
		printf("Error: invalid syntax\n");
	if (!matrix_check(matrix))
		printf("Error: invalid syntax\n");
	matrix_to_cmd(matrix);
	return (matrix);
}

static void free_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	main(void)
{
	char	*input;
	char **m;

	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		terminal_interrupt();
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
			m = matrix(input);
			free_matrix(m);
			free(input);
		}
	}
	rl_clear_history();
	return (0);
}
