NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

SRCS = main.c ft_strtok.c
OBJDIR = obj_dir
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
LIB = ./libft/
LIBFT = ./libft/libft.a

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[1;32mCompiling minishell\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
	@echo "\033[1;30mCompilation Complete\033[0m"

$(LIBFT):
	@echo "\033[1;31mCompiling libft\033[0m"
	@make makeall -C $(LIB)

clean:
	@rm -f $(OBJDIR)/*.o
	@echo "\033[1;34mObject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)
	@find . -type f ! -name "*.c" ! -name "*.h" ! -name "Makefile" ! -path "./libft/*" -exec rm -f {} +
	@find . -type d ! -path "./libft" ! -path "." -exec rm -rf {} +
	@echo "\033[34mCleaned Everything."

re: fclean all

.PHONY: all clean fclean re
