Things I (Roh) need to do (for the week):

Remaining Tasks:

************************************************
WRITE NOTES FOR: \
      PARSER/PARSE_REDIR.C \
      EXECUTION/EXECUTE.C \
      EXECUTION/PIPELINE_HELPER.C \
      EXECUTION/EXECUTE_REDIRECTIONS.C \
      EXECUTION/HANDLE_HEREDOC_REDIRECTION.C \
      EXECUTION/MANAGE_PID_LIST.C
************************************************ 

PATH Expansion for Command Execution:

Current Status: You have a placeholder comment indicating that PATH expansion should be performed before calling execve().

Work Left: Implement logic to search through the directories listed in the $PATH environment variable for the executable corresponding to the command name (if it doesn’t include a slash). This step is necessary to locate the proper binary to run.


Implement Built-in Commands to Execution:
(built-ins cant fork unless it is in a pipeline.)
Work Left: You'll have to implement these and decide whether they should run in the parent process (to affect the shell state) or via forking.


Additional Error Handling and Testing:

Work Left: Ensure robust error handling across your execution flow—especially with pipelines and redirections. Testing edge cases (e.g., multiple redirections, missing filenames, ambiguous syntax) is crucial to mimic bash behavior.

Testing Heredoc and Redirection:
Validate that heredoc, input, output, and append redirections behave as expected even when multiple are specified.

Signal Handling and Job Control (Optional/Advanced):

Work Left: If required by your project, you might also implement more advanced features such as proper signal handling for child processes and job control.
