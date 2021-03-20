CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = libft.a
HEADER_FILES = libft.h ./other/get_next_line_bonus.h

# Memory source and object files
DIR_MEM = mem/

SRC_MEM =   ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c

OBJ_MEM = $(SRC_MEM:.c=.o)

# String source and object files
DIR_STR = str/

SRC_STR =   ft_strlen.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strnstr.c \
			ft_strncmp.c \
            ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
            ft_strmapi.c \
            ft_toupper_str_bonus.c \
            ft_cmpstr_bonus.c

OBJ_STR = $(SRC_STR:.c=.o)

# Number source and object files
DIR_NUM = num/

SRC_NUM =   ft_atoi.c \
            ft_itoa.c \
            ft_ultoa_hex_bonus.c \
            ft_ltoa_dec_bonus.c \
            ft_nblen_bonus.c 

OBJ_NUM = $(SRC_NUM:.c=.o)

# Character source and object files
DIR_CHAR = char/

SRC_CHAR =  ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c

OBJ_CHAR = $(SRC_CHAR:.c=.o)

# Print source and object files
DIR_PRINT = print/

SRC_PRINT = ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c

OBJ_PRINT = $(SRC_PRINT:.c=.o)

# Linked List source and object files
DIR_LLIST = llist/

SRC_LLIST = ft_lstnew.c \
            ft_lstadd_front.c \
            ft_lstsize.c \
            ft_lstlast.c \
            ft_lstadd_back.c \
            ft_lstdelone.c \
            ft_lstclear.c \
            ft_lstiter.c \
            ft_lstmap.c

OBJ_LLIST = $(SRC_LLIST:.c=.o)

# Other source and object files
DIR_OTHER = other/

SRC_OTHER = get_next_line_bonus.c \
			get_next_line_utils_bonus.c

OBJ_OTHER = $(SRC_OTHER:.c=.o)

# Combine all source and object files
SRC = 	$(SRC_MEM:%=$(DIR_MEM)%) \
		$(SRC_STR:%=$(DIR_STR)%) \
		$(SRC_NUM:%=$(DIR_NUM)%) \
		$(SRC_CHAR:%=$(DIR_CHAR)%) \
		$(SRC_PRINT:%=$(DIR_PRINT)%) \
		$(SRC_LLIST:%=$(DIR_LLIST)%) \
		$(SRC_OTHER:%=$(DIR_OTHER)%)

DIR_OBJ = obj/
OBJ = 	$(OBJ_MEM:%=$(DIR_OBJ)%) \
		$(OBJ_STR:%=$(DIR_OBJ)%) \
		$(OBJ_NUM:%=$(DIR_OBJ)%) \
		$(OBJ_CHAR:%=$(DIR_OBJ)%) \
		$(OBJ_PRINT:%=$(DIR_OBJ)%) \
		$(OBJ_LLIST:%=$(DIR_OBJ)%) \
		$(OBJ_OTHER:%=$(DIR_OBJ)%)

# Set the VPATH variable
VPATH = $(DIR_MEM):$(DIR_STR):$(DIR_NUM):$(DIR_CHAR):$(DIR_PRINT):$(DIR_LLIST):$(DIR_OTHER)

all: $(DIR_OBJ) $(NAME)

$(DIR_OBJ):
	mkdir $@

$(NAME): $(OBJ)
	ar cr $@ $^

$(DIR_OBJ)%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rdf $(DIR_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re



