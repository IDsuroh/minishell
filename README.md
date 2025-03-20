Things I (Roh) need to do (for the week):

Remaining Tasks:
Things I (Roh) need to do (for the week):

Remaining Tasks:

```bash
❯ bash $ f
f: command not found

❯ bash $ "phrase in quote" || "phrase 'in' quote" || "phrase "in" quote" || 'phrase 'in' quote' || 'phrase "in" quote'
phrase in quote: command not found
phrase 'in' quote: command not found
phrase in quote: command not found
phrase in quote: command not found
phrase "in" quote: command not found
```

```minishell
minishell$ f

Token[0]: f, Type: T_IDENTIFIER

Command #0:
	Pipe #0:
		Argument #0: f
f: No such file or director

minishell$ "phrase in quote" || "phrase 'in' quote" || "phrase "in" quote" || 'phrase 'in' quote' || 'phrase "in" quote'

Token[0]: "phrase in quote", Type: T_IDENTIFIER
Token[1]: ||, Type: T_OR
Token[2]: "phrase 'in' quote", Type: T_IDENTIFIER
Token[3]: ||, Type: T_OR
Token[4]: "phrase ", Type: T_IDENTIFIER
Token[5]: in, Type: T_IDENTIFIER
Token[6]: " quote", Type: T_IDENTIFIER
Token[7]: ||, Type: T_OR
Token[8]: 'phrase ', Type: T_IDENTIFIER
Token[9]: in, Type: T_IDENTIFIER
Token[10]: ' quote', Type: T_IDENTIFIER
Token[11]: ||, Type: T_OR
Token[12]: 'phrase "in" quote', Type: T_IDENTIFIER

Command #0:
	Pipe #0:
		Argument #0: "phrase in quote"
Command #1:
	Pipe #0:
		Argument #0: "phrase 'in' quote"
Command #2:
	Pipe #0:
		Argument #0: "phrase "
		Argument #1: in
		Argument #2: " quote"
Command #3:
	Pipe #0:
		Argument #0: 'phrase '
		Argument #1: in
		Argument #2: ' quote'
Command #4:
	Pipe #0:
		Argument #0: 'phrase "in" quote'
"phrase in quote": No such file or directory
"phrase 'in' quote": No such file or directory
"phrase ": No such file or directory
'phrase ': No such file or directory
'phrase "in" quote': No such file or directory
```

**NOTE: Must strip quotes during parsing.

===============================================================================================================================================================================

Optimize builtins:

export:

unset:

exit:

===============================================================================================================================================================================

Implement this:

All allocated memory at execution time needs to have a reference in almighty,
and needs to be freed from almighty and set to NULL during normal execution to avoid double frees.
It needs to be there so that if _exit _() is called it can free it before exit().
Otherwise just change the _exit _() parameters to add the other structures to free them.

===============================================================================================================================================================================

Additional Error Handling and Testing:

Work Left: Ensure robust error handling across your execution flow—especially with pipelines and redirections. Testing edge cases (e.g., multiple redirections, missing filenames, ambiguous syntax) is crucial to mimic bash behavior.

Testing Heredoc and Redirection:
Validate that heredoc, input, output, and append redirections behave as expected even when multiple are specified.

Signal Handling and Job Control (Optional/Advanced):

Work Left: If required by your project, you might also implement more advanced features such as proper signal handling for child processes and job control.
