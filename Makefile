CC = clang
CFLAGS = -g -fsanitize=address

# Setting variables depending on Operating System
ifdef IS_LINUX
LINKS = -D IS_LINUX=1 -Lmlx_linux -lmlx -lXext -lX11 -lm -lz
MLX_DIR = mlx_linux
else
LINKS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_DIR = mlx
endif

# Output file which is the executable
NAME = exec

# The name of the library that is created by mlx
MLX_LIB = libmlx.a

# Libft (including get_next_line)
LIBFT = libft.a
LIBFT_DIR = libft

# Source files
#DIR_MAIN = 
SRC_MAIN = main.c

DIR_PARSER = parser
SRC_PARSER =	parse_main.c \
				parse_data.c \
				init.c \
				parse_resolution.c \
				parse_texture.c \
				parse_colour.c \
				parse_map.c \
				utils.c

SRC = $(SRC_MAIN) $(SRC_PARSER)

# Object files
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

VPATH = $(DIR_PARSER)

all: $(OBJ_DIR) $(MLX_LIB) $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir $@

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINKS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(LINKS) -c $< -o $@

clean:
	rm -rdf $(OBJ_DIR)
	make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
