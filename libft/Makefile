CC=CC
CFLAGS= -Wall -Werror -Wextra
AR=ar rc
RM=rm -rf

FILES= ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_strlen \
	   ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp \
	   ft_strnstr ft_strlcpy ft_strlcat ft_atoi ft_strdup \
	   ft_substr ft_strjoin ft_split ft_itoa ft_strmapi \
	   ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_isprint \
	   ft_putnbr_fd ft_strtrim ft_memcpy ft_memmove ft_memset \
	   ft_memcmp ft_memchr ft_bzero ft_calloc ft_striteri ft_strcmp

BFILES  =	ft_lstnew_bonus ft_lstadd_front_bonus \
			ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus \
			ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus

OBJ=$(FILES:=.o)
BOBJ=$(BFILES:=.o)
NAME=libft.a

all: $(NAME)

bonus: $(BOBJ)
	$(AR) $(NAME) $(BOBJ)

%.o			:	%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ) $(BOBJ)

fclean: clean
	@$(RM) $(NAME)
re: fclean all

.PHONY: all bonus clean fclean re