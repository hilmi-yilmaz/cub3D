CC = clang

ifdef VALGRIND
CFLAGS = -g3 
else
CFLAGS = -g3 -fsanitize=address
endif

# Setting variables depending on Operating System
ifdef __linux__
LINKS = -D __linux__=1 -Lmlx_linux -lmlx -lXext -lX11 -lm -lz
MLX_DIR = mlx_linux
else
LINKS = -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_DIR = mlx
endif

# Output file which is the executable
NAME = exec

# The name of the library that is created by mlx
MLX_LIB = libmlx.a

# Headerfile
HEADER_FILE = cub3d.h

# Libft (including get_next_line)
LIBFT = libft.a
LIBFT_DIR = libft

# Source files
SRC_MAIN = main.c

DIR_PARSER = 	parser
SRC_PARSER =	parse_main.c \
				parse_data.c \
				init.c \
				parse_resolution.c \
				parse_texture.c \
				parse_colour.c \
				parse_map.c \
				flood_fill.c \
				free_data.c \
				utils.c \
				checks.c \
				print.c

DIR_RAYCASTER = raycaster
SRC_RAYCASTER = main.c \
				init_data.c \
				free_data.c \
				hooks.c \
				checks.c \
				math.c \
				intersections.c \
				utils.c \
				cast_rays.c \
				print_data.c \
				map_to_3d_textured.c \
				gameplay.c \
				load_xpm.c

# Object files
OBJ_DIR = obj
OBJ_MAIN = $(SRC_MAIN:%.c=$(OBJ_DIR)/%.o)
OBJ_PARSER = $(SRC_PARSER:%.c=$(OBJ_DIR)/$(DIR_PARSER)/%.o)
OBJ_RAYCASTER = $(SRC_RAYCASTER:%.c=$(OBJ_DIR)/$(DIR_RAYCASTER)/%.o)
OBJ = $(OBJ_MAIN) $(OBJ_PARSER) $(OBJ_RAYCASTER)

VPATH = $(DIR_PARSER) $(DIR_RAYCASTER)

all: $(OBJ_DIR) $(MLX_LIB) $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir -p $@/$(DIR_PARSER)
	mkdir -p $@/$(DIR_RAYCASTER)

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINKS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

$(OBJ) : $(OBJ_DIR)/%.o: %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rdf $(OBJ_DIR)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all
