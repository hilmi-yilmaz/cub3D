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
				parse_resolution.c \
				parse_texture.c \
				parse_colour.c \
				parse_map.c \
				checks/check_data_completeness.c \
				checks/check_map.c \
				utils/init.c \
				utils/parser_free.c \
				utils/parser_utils.c \
				utils/print.c

INC_PARSER = 	parse_structs.h \
				parse_main.h \
				parse_data.h \
				parse_resolution.h \
				parse_texture.h \
				parse_colour.h \
				parse_map.h \
				checks/check_data_completeness.h \
				checks/check_map.h \
				utils/init.h \
				utils/parser_utils.h \
				utils/parser_free.h \
				utils/print.h

DIR_RAYCASTER = raycaster
SRC_RAYCASTER = main.c \
				init_data.c \
				hooks.c \
				checks.c \
				math.c \
				intersections.c \
				cast_rays.c \
				print_data.c \
				map_to_3d_textured.c \
				gameplay.c \
				load_xpm.c \
				utils/raycaster_free.c \
				utils/raycaster_utils.c

INC_RAYCASTER = raycaster_structs.h \
				main.h \
				init_data.h \
				hooks.h \
				checks.h \
				math.h \
				intersections.h \
				cast_rays.h \
				print_data.h \
				map_to_3d_textured.h \
				gameplay.h \
				load_xpm.h \
				utils/raycaster_free.h \
				utils/raycaster_utils.h

# Headerfiles
HEADER_FILES = cub3d.h $(INC_PARSER) $(INC_RAYCASTER)

# Object files
OBJ_DIR = obj
OBJ_MAIN = $(SRC_MAIN:%.c=$(OBJ_DIR)/%.o)
OBJ_PARSER = $(SRC_PARSER:%.c=$(OBJ_DIR)/$(DIR_PARSER)/%.o)
OBJ_RAYCASTER = $(SRC_RAYCASTER:%.c=$(OBJ_DIR)/$(DIR_RAYCASTER)/%.o)
OBJ = $(OBJ_MAIN) $(OBJ_PARSER) $(OBJ_RAYCASTER) $(OBJ_UTILS)

VPATH = $(DIR_PARSER) $(DIR_RAYCASTER)

all: $(OBJ_DIR) $(MLX_LIB) $(LIBFT) $(NAME)

$(OBJ_DIR):
	mkdir -p $@/$(DIR_PARSER)
	mkdir -p $@/$(DIR_PARSER)/checks
	mkdir -p $@/$(DIR_PARSER)/utils
	mkdir -p $@/$(DIR_RAYCASTER)
	mkdir -p $@/$(DIR_RAYCASTER)/utils

$(MLX_LIB):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINKS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

$(OBJ) : $(OBJ_DIR)/%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rdf $(OBJ_DIR)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean all
