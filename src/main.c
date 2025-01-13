/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/01/13 00:01:46 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/colors.h"

static const char *token_type_to_string(t_token_type type)
{
	switch (type)
	{
		case T_IDENTIFIER: return "T_IDENTIFIER";
		case T_LESS: return "T_LESS";
		case T_GREAT: return "T_GREAT";
		case T_DLESS: return "T_DLESS";
		case T_DGREAT: return "T_DGREAT";
		case T_PIPE: return "T_PIPE";
		case T_AND: return "T_AND";
		case T_OR: return "T_OR";
		case T_VAR: return "T_VAR";
		default: return "UNKNOWN";
	}
}

static const char *get_token_color(t_token_type type)
{
	switch (type)
	{
		case T_IDENTIFIER: return GREEN;    // You can choose any color for identifier
		case T_LESS: return BLUE;          // Color for 'less than' token
		case T_GREAT: return BLUE;         // Color for 'greater than' token
		case T_DLESS: return MAGENTA;      // Color for 'double less than' token
		case T_DGREAT: return MAGENTA;     // Color for 'double greater than' token
		case T_PIPE: return CYAN;          // Color for pipe
		case T_AND: return RED;            // Color for 'and' token
		case T_OR: return RED;             // Color for 'or' token
		case T_VAR: return YELLOW;         // Color for variable
		default: return RESET;             // Default color (reset to normal)
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token_node	**current;
	char			*input;

	((void)argc, (void)argv);
	(void)envp;
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		current = tokenizer(input);
		free(input);
		for (int i = 0; current[i] != NULL ; i++)
		{
			printf("Token[%d]: %s%s%s, Type: %s%s%s\n",
				i,
				get_token_color(current[i]->type), current[i]->token_value, RESET,
				get_token_color(current[i]->type), token_type_to_string(current[i]->type), RESET);
			/*printf("Token[%d]: %s, Type: %s\n",
				i,
				current->token_value,
				token_type_to_string(current->type));*/
		}
		free_node_list(current);
	}
	return (0);
}
