/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suroh <suroh@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:57:19 by suroh             #+#    #+#             */
/*   Updated: 2025/01/29 19:19:20 by suroh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
//#include "../include/colors.h"

/*
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
		case T_XVAR: return "T_XVAR";
		case T_PID: return "T_PID";
		default: return "UNKNOWN";
	}
}

static const char *get_token_color(t_token_type type)
{
	switch (type)
	{
		case T_IDENTIFIER: return ID;    // You can choose any color for identifier
		case T_LESS: return LSS;          // Color for 'less than' token
		case T_GREAT: return GRT;         // Color for 'greater than' token
		case T_DLESS: return DLSS;      // Color for 'double less than' token
		case T_DGREAT: return DGRT;     // Color for 'double greater than' token
		case T_PIPE: return PP;          // Color for pipe
		case T_AND: return ND;            // Color for 'and' token
		case T_OR: return OR;             // Color for 'or' token
		case T_VAR: return VR;         // Color for variable
		case T_XVAR: return XVR;        // Color for environment pointer variable
		case T_PID: return PD;         // Color for process id variable
		default: return RESET;             // Default color (reset to normal)
	}
}
*/

int	main(int argc, char **argv, char **envp)
{
	t_pipe_sequence	*tmp_seq;
	t_pipe_sequence	*head_seq;
	t_token_node	**current;
	t_redir		*redir;
//	t_operator	*operator;
	char			*input;
	int				cmd_idx;

	((void)argc, (void)argv);
	(void)envp;
	init_signals();
	while (1)
	{
		input = readline("minishell$ ");
		terminal_interrupt();
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		current = tokenizer(input);
		free(input);
		if (current == NULL)
			continue ;
		tmp_seq = parse_tokens(current);
		head_seq = tmp_seq;
		cmd_idx = 0;
		while (tmp_seq)
		{
			printf("Command #%d:\n", cmd_idx);
			if (tmp_seq->cmd && tmp_seq->cmd->argv)
			{
				for (int i = 0; tmp_seq->cmd->argv[i]; i++)
					printf("  Arg[%d]: %s\n", i, tmp_seq->cmd->argv[i]);
				redir = tmp_seq->cmd->redir;
				while (redir)
				{
					printf("  Redirection: type=%d -> %s\n",
							redir->type, redir->filename);
					redir = redir->next;
				}
				/*operator = tmp_seq->cmd->op;
				while (operator)
				{
					printf("  Operator: type=%d\n", operator->type);
					operator = operator->next;
				}*/
			}
			tmp_seq = tmp_seq->next;
			cmd_idx++;
		}
		free_pipeline(head_seq);
		free_node_list(current);
	}
	return (0);
}

/* ************************************************************************** */
//	Loop to check Tokenizer output:
//
//		for (int i = 0; current[i] != NULL ; i++)
//		{
//			printf("Token[%d]: %s%s%s, Type: %s%s%s\n",
//				i,
//				get_token_color(current[i]->type), current[i]->token_value, RESET,
//				get_token_color(current[i]->type), token_type_to_string(current[i]->type), RESET);
//			/*printf("Token[%d]: %s, Type: %s\n",
//				i,
//				current->token_value,
//				token_type_to_string(current->type));*/
//		}

