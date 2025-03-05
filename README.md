Things I (Roh) need to do (for the weekend):

1. Write explanation for;
  a. Tokenization
  b. Error Check
  c. Parsing
  d. Printing logic of Tokenization and Parsing.

============================================================================================================================================================================================================

2. Expand Environment Variables (T_VAR)
   2.1. $$ and $? how to do them.
   * figured out $$ but not $?

static char	*fetch_env_value(char *var_name, t_list_header *var_list)
{
	t_var_elm	*env_var;

	if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(get_pid_from_proc()));
	if (ft_strcmp(var_name, "?") == 0)
		return ("\t***for now not implemented\t***");
	env_var = get_value(var_list, var_name);
	if (env_var)
		return (env_var->value);
	return ("");
}

❯ valgrind --track-fds=yes --track-origins=yes --leak-check=full ./minishell
==10433== Memcheck, a memory error detector
==10433== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==10433== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==10433== Command: ./minishell
==10433== 
minishell$ "$HELLO $$"

Token[0]: " 10433", Type: T_VAR

Command #0:
	Pipe #0:
		Argument #0: " 10433"
minishell$ "$HELLO $$ $?"

Token[0]: " 10433 	***for now not implemented	***", Type: T_VAR

Command #0:
	Pipe #0:
		Argument #0: " 10433 	***for now not implemented	***"
minishell$ "$HELLO $$ $?" $$ $?

Token[0]: " 10433 	***for now not implemented	***", Type: T_VAR
Token[1]: $$, Type: T_PID
Token[2]: $?, Type: T_XVAR

Command #0:
	Pipe #0:
		Argument #0: " 10433 	***for now not implemented	***"
		Argument #1: $$
		Argument #2: $?
minishell$ 
==10433== 
==10433== FILE DESCRIPTORS: 3 open (3 std) at exit.
==10433== 
==10433== HEAP SUMMARY:
==10433==     in use at exit: 233,010 bytes in 249 blocks
==10433==   total heap usage: 729 allocs, 480 frees, 259,575 bytes allocated
==10433== 
==10433== 18 bytes in 3 blocks are definitely lost in loss record 15 of 82
==10433==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==10433==    by 0x10D343: ft_calloc (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==10433==    by 0x10D76C: ft_itoa (in /home/suroh/Documents/42_Common_Core/M3/minishell/minishell)
==10433==    by 0x10A048: fetch_env_value (env_expansion.c:32)
==10433==    by 0x10A122: replace_variable (env_expansion.c:55)
==10433==    by 0x10A1A7: expand_token_value (env_expansion.c:72)
==10433==    by 0x10A260: expand_env_variables (env_expansion.c:90)
==10433==    by 0x1096B8: handle_input (main.c:97)
==10433==    by 0x10979B: main (main.c:124)
==10433== 
==10433== 48 bytes in 3 blocks are definitely lost in loss record 26 of 82
==10433==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==10433==    by 0x48A70EC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2)
==10433==    by 0x4883E37: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2)
==10433==    by 0x488E8EA: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.2)
==10433==    by 0x109722: main (main.c:112)
==10433== 
==10433== LEAK SUMMARY:
==10433==    definitely lost: 66 bytes in 6 blocks
==10433==    indirectly lost: 0 bytes in 0 blocks
==10433==      possibly lost: 0 bytes in 0 blocks
==10433==    still reachable: 232,944 bytes in 243 blocks
==10433==         suppressed: 0 bytes in 0 blocks
==10433== Reachable blocks (those to which a pointer was found) are not shown.
==10433== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==10433== 
==10433== For lists of detected and suppressed errors, rerun with: -s
==10433== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

============================================================================================================================================================================================================

3. Findout what redirections are. (Understand the concept in a deeper scale)

============================================================================================================================================================================================================

4. Findout what to do after these process.


*Check if string expansion (e.g. $HOME, $USER) happens before tokenization or after.
*What is string expansions and how is it different with environmental variable?
