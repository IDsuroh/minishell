Things I (Roh) need to do (for the week):

Remaining Tasks:

Implement this:

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



Mon Mar 17 06:38:08 PM WET 2025
As per Roh's request, here are the valgrind errors during minishell's execution:

c2r2s7% ./minishell 
minishell$ ls

Token[0]: ls, Type: T_IDENTIFIER

Command #0:
	Pipe #0:
		Argument #0: ls
free(): double free detected in tcache 2
minishell$ ^C
c2r2s7% valgrind ./minishell 
==42231== Memcheck, a memory error detector
==42231== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==42231== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==42231== Command: ./minishell
==42231== 
minishell$ ls

Token[0]: ls, Type: T_IDENTIFIER

Command #0:
	Pipe #0:
		Argument #0: ls
==42232== Invalid read of size 8
==42232==    at 0x406A0B: free_paths (find_executable_helper.c:27)
==42232==    by 0x406813: find_executable (find_executable.c:75)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232==  Address 0x4b65de8 is 8 bytes inside a block of size 88 free'd
==42232==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42232==    by 0x406A1E: free_paths (find_executable_helper.c:29)
==42232==    by 0x406813: find_executable (find_executable.c:75)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232==  Block was alloc'd at
==42232==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42232==    by 0x4073DD: ft_calloc (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42232==    by 0x407754: ft_split (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42232==    by 0x406880: get_path_directories (find_executable.c:60)
==42232==    by 0x4067D8: find_executable (find_executable.c:71)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232== 
==42232== Invalid free() / delete / delete[] / realloc()
==42232==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42232==    by 0x406A1E: free_paths (find_executable_helper.c:29)
==42232==    by 0x406813: find_executable (find_executable.c:75)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232==  Address 0x4b65de0 is 0 bytes inside a block of size 88 free'd
==42232==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42232==    by 0x406A1E: free_paths (find_executable_helper.c:29)
==42232==    by 0x406813: find_executable (find_executable.c:75)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232==  Block was alloc'd at
==42232==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42232==    by 0x4073DD: ft_calloc (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42232==    by 0x407754: ft_split (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42232==    by 0x406880: get_path_directories (find_executable.c:60)
==42232==    by 0x4067D8: find_executable (find_executable.c:71)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232== 
==42232== Invalid free() / delete / delete[] / realloc()
==42232==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42232==    by 0x406A35: free_paths (find_executable_helper.c:32)
==42232==    by 0x406813: find_executable (find_executable.c:75)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232==  Address 0x4b65de0 is 0 bytes inside a block of size 88 free'd
==42232==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42232==    by 0x406A1E: free_paths (find_executable_helper.c:29)
==42232==    by 0x406813: find_executable (find_executable.c:75)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232==  Block was alloc'd at
==42232==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42232==    by 0x4073DD: ft_calloc (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42232==    by 0x407754: ft_split (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42232==    by 0x406880: get_path_directories (find_executable.c:60)
==42232==    by 0x4067D8: find_executable (find_executable.c:71)
==42232==    by 0x405C9E: execute_child_command (execute.c:22)
==42232==    by 0x405D76: execute_command (execute.c:60)
==42232==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42232==    by 0x40145A: process_tokens (handle_input.c:72)
==42232==    by 0x401366: handle_input (handle_input.c:100)
==42232==    by 0x4016EF: shell_loop (main.c:39)
==42232==    by 0x4015FF: main (main.c:52)
==42232== 
builtins  envp_expand  error_check  execution  include	Makefile  minishell  obj_dir  parser  README.md  src  tokenizer
==42231== Conditional jump or move depends on uninitialised value(s)
==42231==    at 0x405E63: execute_parsed_structure (execute.c:79)
==42231==    by 0x40145A: process_tokens (handle_input.c:72)
==42231==    by 0x401366: handle_input (handle_input.c:100)
==42231==    by 0x4016EF: shell_loop (main.c:39)
==42231==    by 0x4015FF: main (main.c:52)
==42231== 
==42231== Conditional jump or move depends on uninitialised value(s)
==42231==    at 0x405E80: execute_parsed_structure (execute.c:81)
==42231==    by 0x40145A: process_tokens (handle_input.c:72)
==42231==    by 0x401366: handle_input (handle_input.c:100)
==42231==    by 0x4016EF: shell_loop (main.c:39)
==42231==    by 0x4015FF: main (main.c:52)
==42231== 
minishell$ 
==42231== 
==42231== HEAP SUMMARY:
==42231==     in use at exit: 208,220 bytes in 225 blocks
==42231==   total heap usage: 657 allocs, 432 frees, 233,603 bytes allocated
==42231== 
==42231== LEAK SUMMARY:
==42231==    definitely lost: 0 bytes in 0 blocks
==42231==    indirectly lost: 0 bytes in 0 blocks
==42231==      possibly lost: 0 bytes in 0 blocks
==42231==    still reachable: 208,220 bytes in 225 blocks
==42231==         suppressed: 0 bytes in 0 blocks
==42231== Rerun with --leak-check=full to see details of leaked memory
==42231== 
==42231== Use --track-origins=yes to see where uninitialised values come from
==42231== For lists of detected and suppressed errors, rerun with: -s
==42231== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
c2r2s7% ./minishell 
minishell$ ls

Token[0]: ls, Type: T_IDENTIFIER

Command #0:
	Pipe #0:
		Argument #0: ls
free(): double free detected in tcache 2
minishell$ ls

Token[0]: ls, Type: T_IDENTIFIER

Command #0:
	Pipe #0:
		Argument #0: ls
free(): double free detected in tcache 2
minishell$ pwd

Token[0]: pwd, Type: T_IDENTIFIER

Command #0:
	Pipe #0:
		Argument #0: pwd
free(): double free detected in tcache 2
minishell$ 
c2r2s7% valgrind ./minishell
==42243== Memcheck, a memory error detector
==42243== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==42243== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==42243== Command: ./minishell
==42243== 
minishell$ echo hi

Token[0]: echo, Type: T_IDENTIFIER
Token[1]: hi, Type: T_IDENTIFIER

Command #0:
	Pipe #0:
		Argument #0: echo
		Argument #1: hi
==42244== Invalid read of size 8
==42244==    at 0x406A0B: free_paths (find_executable_helper.c:27)
==42244==    by 0x406813: find_executable (find_executable.c:75)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244==  Address 0x4b66058 is 8 bytes inside a block of size 88 free'd
==42244==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42244==    by 0x406A1E: free_paths (find_executable_helper.c:29)
==42244==    by 0x406813: find_executable (find_executable.c:75)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244==  Block was alloc'd at
==42244==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42244==    by 0x4073DD: ft_calloc (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42244==    by 0x407754: ft_split (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42244==    by 0x406880: get_path_directories (find_executable.c:60)
==42244==    by 0x4067D8: find_executable (find_executable.c:71)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244== 
==42244== Invalid free() / delete / delete[] / realloc()
==42244==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42244==    by 0x406A1E: free_paths (find_executable_helper.c:29)
==42244==    by 0x406813: find_executable (find_executable.c:75)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244==  Address 0x4b66050 is 0 bytes inside a block of size 88 free'd
==42244==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42244==    by 0x406A1E: free_paths (find_executable_helper.c:29)
==42244==    by 0x406813: find_executable (find_executable.c:75)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244==  Block was alloc'd at
==42244==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42244==    by 0x4073DD: ft_calloc (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42244==    by 0x407754: ft_split (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42244==    by 0x406880: get_path_directories (find_executable.c:60)
==42244==    by 0x4067D8: find_executable (find_executable.c:71)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244== 
==42244== Invalid free() / delete / delete[] / realloc()
==42244==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42244==    by 0x406A35: free_paths (find_executable_helper.c:32)
==42244==    by 0x406813: find_executable (find_executable.c:75)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244==  Address 0x4b66050 is 0 bytes inside a block of size 88 free'd
==42244==    at 0x484B27F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42244==    by 0x406A1E: free_paths (find_executable_helper.c:29)
==42244==    by 0x406813: find_executable (find_executable.c:75)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244==  Block was alloc'd at
==42244==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==42244==    by 0x4073DD: ft_calloc (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42244==    by 0x407754: ft_split (in /home/miteixei/projects/42cursus/minishell-github/minishell)
==42244==    by 0x406880: get_path_directories (find_executable.c:60)
==42244==    by 0x4067D8: find_executable (find_executable.c:71)
==42244==    by 0x405C9E: execute_child_command (execute.c:22)
==42244==    by 0x405D76: execute_command (execute.c:60)
==42244==    by 0x405E52: execute_parsed_structure (execute.c:78)
==42244==    by 0x40145A: process_tokens (handle_input.c:72)
==42244==    by 0x401366: handle_input (handle_input.c:100)
==42244==    by 0x4016EF: shell_loop (main.c:39)
==42244==    by 0x4015FF: main (main.c:52)
==42244== 
hi
==42243== Conditional jump or move depends on uninitialised value(s)
==42243==    at 0x405E63: execute_parsed_structure (execute.c:79)
==42243==    by 0x40145A: process_tokens (handle_input.c:72)
==42243==    by 0x401366: handle_input (handle_input.c:100)
==42243==    by 0x4016EF: shell_loop (main.c:39)
==42243==    by 0x4015FF: main (main.c:52)
==42243== 
==42243== Conditional jump or move depends on uninitialised value(s)
==42243==    at 0x405E80: execute_parsed_structure (execute.c:81)
==42243==    by 0x40145A: process_tokens (handle_input.c:72)
==42243==    by 0x401366: handle_input (handle_input.c:100)
==42243==    by 0x4016EF: shell_loop (main.c:39)
==42243==    by 0x4015FF: main (main.c:52)
==42243== 
minishell$ 

