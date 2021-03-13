CC = clang
CFLAGS = -Wall -Wextra -Werror

NAME = exec

MLX_LIB = libmlx.a

SRC = main.c

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(OBJ_DIR) $(MLX_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx -lXext -lX11 -lm -o $(NAME)

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

$(MLX_LIB):
	make -C mlx_linux

clean:
	rm -rdf obj/

fclean: clean
	rm -f $(NAME)

re: fclean all
