NAME	=	minishell
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
LDFLAGS	=	-lreadline

TOKDIR	=	tokenizer
PARDIR	=	parser
SRCDIR	= 	src
ERRDIR	=	error_check
ENVDIR	=	envp_expand
EXCDIR	=	execution
BUILTIN	=	builtins

OBJDIR	= 	obj_dir

VPATH	=	$(SRCDIR):$(TOKDIR):$(PARDIR):$(ERRDIR):$(ENVDIR):$(BUILTIN):$(EXCDIR)

SRC_SRCS	=	main.c \
				print_utils_1.c \
				print_utils_2.c \
				signals.c \
			
TOK_SRCS	=	tokenizer.c \
				tokenize_input.c \
				tokenizer_counters.c \
				tokenizer_flags_1.c \
				tokenizer_flags_2.c \
				tokenizer_flags_3.c \
				tokenizer_helpers.c \
				storage_logic.c \
				storage_logic_helper.c \
				create_node_list.c

PAR_SRCS	=	parser.c \
				parse_sequence.c \
				parse_pipe_sequence.c \
				parse_redir.c \
				parse_command.c \
				parser_helpers.c \
				initiators.c \
				token_access.c \

ERR_SRCS	=	error_check_flags_1.c \
				error_check_flags_2.c \
				open_input_checker.c \

ENV_SRCS	=	envp.c \
				envp_expansion.c \
				envp_expansion_utils_1.c \
				envp_expansion_utils_2.c \
				envp_utils_1.c \
				envp_utils_2.c

EXC_SRCS	=	execute.c \
				execute_pipeline.c \
				execute_pipeline_helper.c \
				execute_redirections.c \
				find_executable.c \
				find_executable_helper.c \
				handle_heredoc_redirection.c \
				manage_pid_list.c

BUIL_SRCS	=	dir.c

SRCS		= 	$(addprefix $(SRCDIR)/, $(SRC_SRCS)) \
				$(addprefix $(TOKDIR)/, $(TOK_SRCS)) \
				$(addprefix $(PARDIR)/, $(PAR_SRCS)) \
				$(addprefix $(ERRDIR)/, $(ERR_SRCS)) \
				$(addprefix $(ENVDIR)/, $(ENV_SRCS)) \
				$(addprefix $(BUILTIN)/, $(BUIL_SRCS)) \
				$(addprefix $(EXCDIR)/, $(EXC_SRCS))

OBJS		= 	$(patsubst %.c, $(OBJDIR)/%.o, $(notdir $(SRCS)))

LIB			=	./include/libft/
LIBFT		=	./include/libft/libft.a

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[1;32mCompiling minishell\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo "\033[1;30mCompilation Complete\033[0m"

$(LIBFT):
	@echo "\033[1;31mCompiling libft\033[0m"
	@make makeall -C $(LIB) --no-print-directory

clean:
	@rm -f $(OBJDIR)/*.o
	@echo "\033[1;34mObject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)
	@rm -f $(LIBFT) $(LIB)/*.o
	@echo "\033[34mCleaned Everything."

re: fclean all

.PHONY: all clean fclean re

# The patsubst (pattern substitution) function takes three arguments:
# 
# The pattern to look for (%.c), meaning “any file ending in .c.”
# The replacement pattern ($(OBJDIR)/%.o), which means “replace .c with
# .o and prepend the object directory path.”
# The list of filenames to process (the output from $(notdir $(SRCS))).
# So, if you have main.c from the previous step and $(OBJDIR) is obj_dir,
# this function transforms main.c into obj_dir/main.o.
#
# $(notdir $(SRCS)):
#
# This function removes the directory part of each file in SRCS,
# leaving only the base filename. For example, if SRCS contains src/main.c,
# $(notdir $(SRCS)) will yield main.c.
