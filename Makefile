CC = gcc
CFLAGS = -g

NAME = exec

MLX_LIB = libmlx.a

SRC = main.c

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(OBJ_DIR) $(MLX_LIB) $(NAME)

ifdef IS_LINUX
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx_linux -lmlx -lXext -lX11 -lm -lz -o $(NAME)
else
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
endif

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $@

$(MLX_LIB):
	make -C mlx

clean:
	rm -rdf obj/

fclean: clean
	rm -f $(NAME)

re: fclean all
