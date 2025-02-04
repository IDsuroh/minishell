# Minishell Project

```sh
***********Correct errors first

## Command Output Examples

❯ ./minishell
minishell$ hello
Command #0:
	Pipe #0:
		Argument #0: hello
minishell$ hello | hello
Command #0:
	Pipe #0:
		Argument #0: hello
	Pipe #1:
		Argument #0: hello
minishell$ hello |||
Command #0:
	Pipe #0:
		Argument #0: hello
minishell$ hello || pwpw
Command #0:
	Pipe #0:
		Argument #0: hello
	Pipe #1:
		Argument #0: pwpw
minishell$ 
exit



1. Need to simply output new prompt when whitespaces or enters are typed.

❯ ./minishell
minishell$ 

[1]    18245 segmentation fault (core dumped)  ./minishell


2. need to simulate:

	pipe>
	
	cmdor>
	
	cmdand>

