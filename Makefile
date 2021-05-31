CC = clang

ifdef VALGRIND
CFLAGS = -g3 
else
CFLAGS = -g3 -fsanitize=address
endif

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

# Headerfile
HEADER_FILE = cub3d.h

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
				free_data.c \
				utils.c

DIR_RAYCASTER = raycaster
SRC_RAYCASTER = raycaster_main.c \
				raycaster_init.c \
				hooks.c \
				checks.c \
				math.c \
				intersections.c \
				raycaster_utils.c \
				draw_elements.c \
				cast_rays.c \
				print_data.c \
				map_to_3d.c

DIR_TEXTURES = 	texture_handling
SRC_TEXTURES = 	scale_bmp.c \
				load_xpm.c \
				v1_scale_bmp.c

SRC = $(SRC_MAIN) $(SRC_PARSER) $(SRC_RAYCASTER) $(SRC_TEXTURES)

# Object files
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

VPATH = $(DIR_PARSER) $(DIR_RAYCASTER) $(DIR_TEXTURES)

all: $(OBJ_DIR) $(MLX_LIB) $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir $@

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) #$(HEADER_FILE)
	$(CC) $(CFLAGS) $(OBJ) $(LINKS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER_FILE)
	$(CC) $(CFLAGS) $(LINKS) -c $< -o $@

clean:
	rm -rdf $(OBJ_DIR)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all
