# Minishell Project

```sh
***********Correct errors first

## Command Output Examples

❯ ./minishell

minishell$ hello || hello
Command #0:
	Pipe #0:
		Argument #0: hello
Command #1:
	Pipe #0:
		Argument #0: hello

minishell$ hello || hello || hello
Command #0:
	Pipe #0:
		Argument #0: hello
Command #1:
	Pipe #0:
		Argument #0: hello
Command #2:
	Pipe #0:
		Argument #0: hello

minishell$ hello || hello ||
Command #0:
	Pipe #0:
		Argument #0: hello
Command #1:
	Pipe #0:
		Argument #0: hello

Problematic Parts;

minishell$ hello | hello ||
Command #0:
	Pipe #0:
		Argument #0: hello

minishell$ hello | hello || hello
Command #0:
	Pipe #0:
		Argument #0: hello

minishell$
Command #0:
	Pipe #0:
		Argument #0:




1. Need to simply output new prompt when whitespaces or enters are typed.
2. need to simulate:

	pipe>
	
	cmdor>
	
	cmdand>

