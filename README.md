Things I (Roh) need to do (for the weekend):

❯ valgrind --leak-check=full --track-fds=yes --track-origins=yes ./minishell\

==7127== Memcheck, a memory error detector
==7127== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==7127== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==7127== Command: ./minishell
==7127== 
minishell$ hello ||hello | hello "%sdfsdf" 'sdfsdf'&&georihgsl"$HOME""$""$$"$$$?"$?"$?$HOME$HOMER'sagid'"HELLO""$?$HOME$USER$PWD"
==7127== Invalid read of size 1
==7127==    at 0x10D2AA: ft_strlen (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10D704: ft_strjoin (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10C5D7: assemble_expanded (env_expansion.c:20)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Address 0x4b087d0 is 0 bytes inside a block of size 12 free'd
==7127==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10C5F3: assemble_expanded (env_expansion.c:22)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Block was alloc'd at
==7127==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10D52B: ft_strdup (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10C459: extract_var (env.c:44)
==7127==    by 0x10C547: init_var_list (env.c:77)
==7127==    by 0x10972A: main (main.c:109)
==7127== 
==7127== Invalid read of size 1
==7127==    at 0x10D7A6: ft_strjoin (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10C5D7: assemble_expanded (env_expansion.c:20)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Address 0x4b087d0 is 0 bytes inside a block of size 12 free'd
==7127==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10C5F3: assemble_expanded (env_expansion.c:22)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Block was alloc'd at
==7127==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10D52B: ft_strdup (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10C459: extract_var (env.c:44)
==7127==    by 0x10C547: init_var_list (env.c:77)
==7127==    by 0x10972A: main (main.c:109)
==7127== 
==7127== Invalid read of size 1
==7127==    at 0x10D78C: ft_strjoin (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10C5D7: assemble_expanded (env_expansion.c:20)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Address 0x4b087d0 is 0 bytes inside a block of size 12 free'd
==7127==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10C5F3: assemble_expanded (env_expansion.c:22)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Block was alloc'd at
==7127==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10D52B: ft_strdup (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10C459: extract_var (env.c:44)
==7127==    by 0x10C547: init_var_list (env.c:77)
==7127==    by 0x10972A: main (main.c:109)
==7127== 
==7127== Invalid free() / delete / delete[] / realloc()
==7127==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10C5F3: assemble_expanded (env_expansion.c:22)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Address 0x4b087d0 is 0 bytes inside a block of size 12 free'd
==7127==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10C5F3: assemble_expanded (env_expansion.c:22)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Block was alloc'd at
==7127==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10D52B: ft_strdup (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10C459: extract_var (env.c:44)
==7127==    by 0x10C547: init_var_list (env.c:77)
==7127==    by 0x10972A: main (main.c:109)
==7127== 

Token[0]: hello, Type: T_IDENTIFIER
Token[1]: ||, Type: T_OR
Token[2]: hello, Type: T_IDENTIFIER
Token[3]: |, Type: T_PIPE
Token[4]: hello, Type: T_IDENTIFIER
Token[5]: "%sdfsdf", Type: T_IDENTIFIER
Token[6]: 'sdfsdf', Type: T_IDENTIFIER
Token[7]: &&, Type: T_AND
Token[8]: georihgsl, Type: T_IDENTIFIER
Token[9]: "/home/suroh", Type: T_VAR
Token[10]: "", Type: T_VAR
Token[11]: "7127", Type: T_VAR
Token[12]: 7127, Type: T_PID
Token[13]: 7127, Type: T_XVAR
Token[14]: "	***for now not implemented***	", Type: T_VAR
Token[15]: 7127, Type: T_XVAR
Token[16]: /home/suroh, Type: T_VAR
Token[17]: , Type: T_VAR
Token[18]: 'sagid', Type: T_IDENTIFIER
Token[19]: "HELLO", Type: T_IDENTIFIER
Token[20]: "	***for now not implemented***	/home/surohsuroh/home/suroh/Documents/42_Common_Core/M3/minishell", Type: T_VAR

Command #0:
	Pipe #0:
		Argument #0: hello
Command #1:
	Pipe #0:
		Argument #0: hello
	Pipe #1:
		Argument #0: hello
		Argument #1: "%sdfsdf"
		Argument #2: 'sdfsdf'
Command #2:
	Pipe #0:
		Argument #0: georihgsl
		Argument #1: "/home/suroh"
		Argument #2: ""
		Argument #3: "7127"
		Argument #4: 7127
		Argument #5: 7127
		Argument #6: "	***for now not implemented***	"
		Argument #7: 7127
		Argument #8: /home/suroh
		Argument #9: 
		Argument #10: 'sagid'
		Argument #11: "HELLO"
		Argument #12: "	***for now not implemented***	/home/surohsuroh/home/suroh/Documents/42_Common_Core/M3/minishell"
minishell$ 
==7127== Invalid free() / delete / delete[] / realloc()
==7127==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10CE27: free_var_list (env_utils_2.c:25)
==7127==    by 0x1097C3: main (main.c:127)
==7127==  Address 0x4b082b0 is 0 bytes inside a block of size 6 free'd
==7127==    at 0x484988F: free (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10C5F3: assemble_expanded (env_expansion.c:22)
==7127==    by 0x10C770: replace_variable (env_expansion.c:59)
==7127==    by 0x10C7B3: expand_token_value (env_expansion.c:71)
==7127==    by 0x10C86F: expand_env_variables (env_expansion.c:89)
==7127==    by 0x1096D8: handle_input (main.c:97)
==7127==    by 0x1097B1: main (main.c:124)
==7127==  Block was alloc'd at
==7127==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x10D52B: ft_strdup (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==7127==    by 0x10C459: extract_var (env.c:44)
==7127==    by 0x10C547: init_var_list (env.c:77)
==7127==    by 0x10972A: main (main.c:109)
==7127== 
==7127== 
==7127== FILE DESCRIPTORS: 3 open (3 std) at exit.
==7127== 
==7127== HEAP SUMMARY:
==7127==     in use at exit: 233,084 bytes in 238 blocks
==7127==   total heap usage: 819 allocs, 586 frees, 262,209 bytes allocated
==7127== 
==7127== 119 bytes in 1 blocks are definitely lost in loss record 26 of 78
==7127==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7127==    by 0x48A70EC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2)
==7127==    by 0x4883E37: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2)
==7127==    by 0x488E8EA: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2)
==7127==    by 0x10973D: main (main.c:112)
==7127== 
==7127== LEAK SUMMARY:
==7127==    definitely lost: 119 bytes in 1 blocks
==7127==    indirectly lost: 0 bytes in 0 blocks
==7127==      possibly lost: 0 bytes in 0 blocks
==7127==    still reachable: 232,965 bytes in 237 blocks
==7127==         suppressed: 0 bytes in 0 blocks
==7127== Reachable blocks (those to which a pointer was found) are not shown.
==7127== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==7127== 
==7127== For lists of detected and suppressed errors, rerun with: -s
==7127== ERROR SUMMARY: 76 errors from 6 contexts (suppressed: 0 from 0)

1. Find the cause of what the hell those are.

============================================================================================================================================================================================================

3. Implement redirections.
	How to check if the files are existing, etc.

============================================================================================================================================================================================================

4. Findout what to do after these process.


*Check if string expansion (e.g. $HOME, $USER) happens before tokenization or after.
*What is string expansions and how is it different with environmental variable?
