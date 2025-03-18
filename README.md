Things I (Roh) need to do (for the week):

Remaining Tasks:

===============================================================================================================================================================================

Solve this issue:
```bash

❯ valgrind --track-fds=yes --track-origins=yes --leak-check=full ./minishell
==30107== Memcheck, a memory error detector
==30107== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==30107== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==30107== Command: ./minishell
==30107== 
minishell$ $$
30107: command not found
minishell$ 
==30107== 
==30107== FILE DESCRIPTORS: 3 open (3 std) at exit.
==30107== 
==30107== HEAP SUMMARY:
==30107==     in use at exit: 232,852 bytes in 238 blocks
==30107==   total heap usage: 676 allocs, 438 frees, 259,991 bytes allocated
==30107== 
==30107== 3 bytes in 1 blocks are definitely lost in loss record 2 of 78
==30107==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==30107==    by 0x10EE13: ft_strdup (in /home/suroh/Documents/minishell/minishell)
==30107==    by 0x10B26A: create_node_list (create_node_list.c:59)
==30107==    by 0x109F75: tokenizer (tokenizer.c:27)
==30107==    by 0x1097B2: handle_input (handle_input.c:83)
==30107==    by 0x10992E: shell_loop (main.c:40)
==30107==    by 0x10999C: main (main.c:53)
==30107== 
==30107== LEAK SUMMARY:
==30107==    definitely lost: 3 bytes in 1 blocks
==30107==    indirectly lost: 0 bytes in 0 blocks
==30107==      possibly lost: 0 bytes in 0 blocks
==30107==    still reachable: 232,849 bytes in 237 blocks
==30107==         suppressed: 0 bytes in 0 blocks
==30107== Reachable blocks (those to which a pointer was found) are not shown.
==30107== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==30107== 
==30107== For lists of detected and suppressed errors, rerun with: -s
==30107== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
❯ valgrind --track-fds=yes --track-origins=yes --leak-check=full ./minishell
==30110== Memcheck, a memory error detector
==30110== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==30110== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==30110== Command: ./minishell
==30110== 
minishell$ $?
0: command not found
minishell$ $?
0: command not found
minishell$ $?
0: command not found
minishell$ $?
0: command not found
minishell$ $?
0: command not found
minishell$ $?
0: command not found
minishell$ 
==30110== 
==30110== FILE DESCRIPTORS: 3 open (3 std) at exit.
==30110== 
==30110== HEAP SUMMARY:
==30110==     in use at exit: 233,062 bytes in 258 blocks
==30110==   total heap usage: 751 allocs, 493 frees, 260,857 bytes allocated
==30110== 
==30110== 18 bytes in 6 blocks are definitely lost in loss record 14 of 78
==30110==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==30110==    by 0x10EE13: ft_strdup (in /home/suroh/Documents/minishell/minishell)
==30110==    by 0x10B26A: create_node_list (create_node_list.c:59)
==30110==    by 0x109F75: tokenizer (tokenizer.c:27)
==30110==    by 0x1097B2: handle_input (handle_input.c:83)
==30110==    by 0x10992E: shell_loop (main.c:40)
==30110==    by 0x10999C: main (main.c:53)
==30110== 
==30110== LEAK SUMMARY:
==30110==    definitely lost: 18 bytes in 6 blocks
==30110==    indirectly lost: 0 bytes in 0 blocks
==30110==      possibly lost: 0 bytes in 0 blocks
==30110==    still reachable: 233,044 bytes in 252 blocks
==30110==         suppressed: 0 bytes in 0 blocks
==30110== Reachable blocks (those to which a pointer was found) are not shown.
==30110== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==30110== 
==30110== For lists of detected and suppressed errors, rerun with: -s
==30110== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
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
