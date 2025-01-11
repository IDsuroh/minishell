/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/01/11 15:01:31 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//#include "../include/colors.h"

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
		case T_OP_PAR: return "T_OP_PAR";
		case T_CL_PAR: return "T_CL_PAR";
		case T_AND: return "T_AND";
		case T_OR: return "T_OR";
		default: return "UNKNOWN";
	}
}

/*static const char *get_token_color(t_token_type type)
{
	switch (type)
	{
		case T_IDENTIFIER: return GREEN;    // You can choose any color for identifier
		case T_LESS: return BLUE;          // Color for 'less than' token
		case T_GREAT: return BLUE;         // Color for 'greater than' token
		case T_DLESS: return MAGENTA;      // Color for 'double less than' token
		case T_DGREAT: return MAGENTA;     // Color for 'double greater than' token
		case T_PIPE: return CYAN;          // Color for pipe
		case T_OP_PAR: return YELLOW;      // Color for opening parenthesis
		case T_CL_PAR: return YELLOW;      // Color for closing parenthesis
		case T_AND: return RED;            // Color for 'and' token
		case T_OR: return RED;             // Color for 'or' token
		default: return RESET;             // Default color (reset to normal)
	}
}*/

int	main(int argc, char **argv, char **envp)
{
	t_token_node	*token;
	t_token_node	*current;
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
		token = ft_tokenizer(input);
		if (!token)
		{ 
			free(input);
			continue ;
		}
		free(input);
		current = token;
		for (int i = 0; current != NULL ; i++)
		{
			/*printf("Token[%d]: %s%s%s, Type: %s%s%s\n",
				i,
				get_token_color(current->type), current->token_value, RESET,
				get_token_color(current->type), token_type_to_string(current->type), RESET);*/
			printf("Token[%d]: %s, Type: %s\n",
				i,
				current->token_value,
				token_type_to_string(current->type));
			current = current->next;
		}
		ft_free_token_list(token);
		ft_free_token_list(current);
	}
	return (0);
}
