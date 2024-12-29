NAME = libft.a

SRC = 	ft_atoi.c ft_isdigit.c ft_memmove.c ft_strlen.c ft_toupper.c \
	ft_bzero.c ft_isprint.c ft_memset.c ft_strncmp.c ft_isalnum.c \
	ft_memchr.c ft_strchr.c ft_strnstr.c ft_isalpha.c ft_memcmp.c \
	ft_strlcat.c ft_strrchr.c ft_isascii.c ft_memcpy.c ft_strlcpy.c \
	ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[33m-------------LIBFT--------------"
	@ar crs $(NAME) $(OBJ)
	@echo "\033[32m------Compilation Complete------"

bonus: $(OBJ_B)
	@ar crs $(NAME) $(OBJ_B)
	@echo "\033[32m------Bonus Compilation Complete------"

makeall: $(OBJ) $(OBJ_B)
	@ar crs $(NAME) $(OBJ) $(OBJ_B)
	@echo "\033[33m------Compiled Whole File------"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(OBJ_B)
	@echo "\033[36m------All Obj files removed.------"

fclean: clean
	@rm -f $(NAME)
	@echo "-----------fclean------------"

re: fclean all

reall: fclean makeall

.PHONY: all clean fclean re reall
