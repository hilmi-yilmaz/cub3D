CC = gcc
CFLAGS = -g

# Setting variables depending on Operating System
ifdef IS_LINUX
OS_FLAGS = -Lmlx_linux -lmlx -lXext -lX11 -lm -lz -D IS_LINUX
MLX_DIR = mlx_linux
else
OS_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_DIR = mlx
endif

NAME = exec

MLX_LIB = libmlx.a

SRC = main.c

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(OBJ_DIR) $(MLX_LIB) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(O_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

$(MLX_LIB):
	make -C $(MLX_DIR)

clean:
	rm -rdf obj/
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
