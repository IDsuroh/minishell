### For Parser Memory Issue Correction

```sh
❯ cd sdfsdf 2>file
❯ cd sdfsdf 2 >file
❯ cd sdfsdf 2                 >file


❯ valgrind --leak-check=full --track-fds=yes --track-origins=yes ./minishell
==12339== Memcheck, a memory error detector
==12339== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==12339== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==12339== Command: ./minishell
==12339== 
minishell$ a
Command #0:
	Pipe #0:
		Argument #0: a
minishell$ a | b
Command #0:
	Pipe #0:
		Argument #0: a
	Pipe #1:
		Argument #0: b
minishell$ a | b | c
Command #0:
	Pipe #0:
		Argument #0: a
	Pipe #1:
		Argument #0: b
	Pipe #2:
		Argument #0: c
minishell$ a || b
Command #0:
	Pipe #0:
		Argument #0: a
Command #1:
	Pipe #0:
		Argument #0: b
minishell$ a && b
Command #0:
	Pipe #0:
		Argument #0: a
Command #1:
	Pipe #0:
		Argument #0: b
minishell$ 
minishell$ 
minishell$ 
minishell$ 
minishell$ 
minishell$     
minishell$ 
minishell$ a | b || c && d
Command #0:
	Pipe #0:
		Argument #0: a
	Pipe #1:
		Argument #0: b
Command #1:
	Pipe #0:
		Argument #0: c
Command #2:
	Pipe #0:
		Argument #0: d
minishell$ echo "Hello World" | grep "World"
Command #0:
	Pipe #0:
		Argument #0: echo
		Argument #1: "Hello World"
	Pipe #1:
		Argument #0: grep
		Argument #1: "World"
minishell$ ls -la | grep "\.c" && echo "C files found" || echo "No C files found"
Command #0:
	Pipe #0:
		Argument #0: ls
		Argument #1: -la
	Pipe #1:
		Argument #0: grep
		Argument #1: "\.c"
Command #1:
	Pipe #0:
		Argument #0: echo
		Argument #1: "C files found"
Command #2:
	Pipe #0:
		Argument #0: echo
		Argument #1: "No C files found"
minishell$ cat input.txt | sort | uniq -c
Command #0:
	Pipe #0:
		Argument #0: cat
		Argument #1: input.txt
	Pipe #1:
		Argument #0: sort
	Pipe #2:
		Argument #0: uniq
		Argument #1: -c
minishell$ mkdir new_dir && cd new_dir || echo "Failed to create and change directory"
Command #0:
	Pipe #0:
		Argument #0: mkdir
		Argument #1: new_dir
Command #1:
	Pipe #0:
		Argument #0: cd
		Argument #1: new_dir
Command #2:
	Pipe #0:
		Argument #0: echo
		Argument #1: "Failed to create and change directory"
minishell$ command1 && command2 || command3 && command4
Command #0:
	Pipe #0:
		Argument #0: command1
Command #1:
	Pipe #0:
		Argument #0: command2
Command #2:
	Pipe #0:
		Argument #0: command3
Command #3:
	Pipe #0:
		Argument #0: command4
minishell$    ps    aux   |    grep   "minishell"  
Command #0:
	Pipe #0:
		Argument #0: ps
		Argument #1: aux
	Pipe #1:
		Argument #0: grep
		Argument #1: "minishell"
minishell$ make && make install || echo "Build or Install Failed"
Command #0:
	Pipe #0:
		Argument #0: make
Command #1:
	Pipe #0:
		Argument #0: make
		Argument #1: install
Command #2:
	Pipe #0:
		Argument #0: echo
		Argument #1: "Build or Install Failed"
minishell$ 
exit
==12339== 
==12339== FILE DESCRIPTORS: 3 open (3 std) at exit.
==12339== 
==12339== HEAP SUMMARY:
==12339==     in use at exit: 237,547 bytes in 552 blocks
==12339==   total heap usage: 1,038 allocs, 486 frees, 296,319 bytes allocated
==12339== 
==12339== 168 bytes in 7 blocks are definitely lost in loss record 31 of 88
==12339==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12339==    by 0x10B204: malloc_t_op_sequence (initiators.c:19)
==12339==    by 0x10AB7A: parse_sequence (parse_sequence.c:47)
==12339==    by 0x10AA76: parse_tokens (parser.c:32)
==12339==    by 0x109341: main (main.c:92)
==12339== 
==12339== 320 bytes in 20 blocks are definitely lost in loss record 33 of 88
==12339==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12339==    by 0x10AA3E: parse_tokens (parser.c:28)
==12339==    by 0x109341: main (main.c:92)
==12339== 
==12339== 1,538 (1,152 direct, 386 indirect) bytes in 72 blocks are definitely lost in loss record 52 of 88
==12339==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12339==    by 0x10A907: create_node_list (create_node_list.c:52)
==12339==    by 0x1095E5: tokenizer (tokenizer.c:27)
==12339==    by 0x10931A: main (main.c:83)
==12339== 
==12339== 1,800 (416 direct, 1,384 indirect) bytes in 26 blocks are definitely lost in loss record 54 of 88
==12339==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==12339==    by 0x10B249: malloc_t_pipe_sequence (initiators.c:31)
==12339==    by 0x10AC49: append_command (parse_pipe_sequence.c:21)
==12339==    by 0x10AD10: parse_pipe_sequence (parse_pipe_sequence.c:46)
==12339==    by 0x10ABD0: parse_sequence (parse_sequence.c:56)
==12339==    by 0x10AA76: parse_tokens (parser.c:32)
==12339==    by 0x109341: main (main.c:92)
==12339== 
==12339== LEAK SUMMARY:
==12339==    definitely lost: 2,056 bytes in 125 blocks
==12339==    indirectly lost: 1,770 bytes in 151 blocks
==12339==      possibly lost: 0 bytes in 0 blocks
==12339==    still reachable: 233,721 bytes in 276 blocks
==12339==         suppressed: 0 bytes in 0 blocks
==12339== Reachable blocks (those to which a pointer was found) are not shown.
==12339== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==12339== 
==12339== For lists of detected and suppressed errors, rerun with: -s
==12339== ERROR SUMMARY: 4 errors from 4 contexts (suppressed: 0 from 0)
