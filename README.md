Things I (Roh) need to do (for the week):

Remaining Tasks:

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
