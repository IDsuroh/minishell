NAME	=	minishell
CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
LDFLAGS	=	-lreadline

TOKDIR	=	tokenizer
PARDIR	=	parser
SRCDIR	= 	src
ERRDIR	=	error_check

OBJDIR	= 	obj_dir

SRC_SRCS	=	main.c \
			print_utils_1.c \
			print_utils_2.c \
			signals.c

TOK_SRCS	=	tokenizer.c \
			tokenize_input.c \
			tokenizer_counters.c \
			counter_helpers.c \
			tokenizer_flags_1.c \
			tokenizer_flags_2.c \
			tokenizer_helpers.c \
			storage_logic.c \
			env_storage_helper.c \
			create_node_list.c

PAR_SRCS	=	parser.c \
			parse_sequence.c \
			parse_pipe_sequence.c \
			parse_command.c \
			parser_helpers.c \
			initiators.c \
			token_access.c \

ERR_SRCS	=	error_check.c

SRCS	= 	$(addprefix $(SRCDIR)/, $(SRC_SRCS)) \
		$(addprefix $(TOKDIR)/, $(TOK_SRCS)) \
		$(addprefix $(PARDIR)/, $(PAR_SRCS)) \
		$(addprefix $(ERRDIR)/, $(ERR_SRCS))

OBJS	= 	$(addprefix $(OBJDIR)/, $(SRC_SRCS:.c=.o)) \
		$(addprefix $(OBJDIR)/, $(TOK_SRCS:.c=.o)) \
		$(addprefix $(OBJDIR)/, $(PAR_SRCS:.c=.o)) \
		$(addprefix $(OBJDIR)/, $(ERR_SRCS:.c=.o))

LIB	=	./include/libft/
LIBFT	=	./include/libft/libft.a

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(OBJDIR)/%.o: $(TOKDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(OBJDIR)/%.o: $(PARDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(OBJDIR)/%.o: $(ERRDIR)/%.c
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
