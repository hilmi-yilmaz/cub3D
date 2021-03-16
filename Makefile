CC = gcc
CFLAGS = -fsanitize=address -g

# Setting variables depending on Operating System
ifdef IS_LINUX
OS_FLAGS = -Lmlx_linux -lmlx -lXext -lX11 -lm -lz -D IS_LINUX=1
MLX_DIR = mlx_linux/
else
OS_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_DIR = mlx/
endif

NAME = exec

SRC = v1_main.c

MLX_LIB = libmlx.a

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(OBJ_DIR) $(MLX_LIB) $(NAME)

$(OBJ_DIR):
	mkdir $@

$(MLX_LIB):
	make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(OS_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rdf obj/
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
