Things I (Roh) need to do (for the week):

Remaining Tasks:

Implement this;
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
			tokens[i]->token_value = ft_strdup("\tfor now not implemented\t");
			free(old_value);
		}
	}
}

Additional Error Handling and Testing:

Work Left: Ensure robust error handling across your execution flow—especially with pipelines and redirections. Testing edge cases (e.g., multiple redirections, missing filenames, ambiguous syntax) is crucial to mimic bash behavior.

Testing Heredoc and Redirection:
Validate that heredoc, input, output, and append redirections behave as expected even when multiple are specified.

Signal Handling and Job Control (Optional/Advanced):

Work Left: If required by your project, you might also implement more advanced features such as proper signal handling for child processes and job control.
