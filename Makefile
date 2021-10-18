CC = clang
CFLAGS = -g -Wall -Wextra -Werror

ifdef VALGRIND
CFLAGS = -g3 -Wall -Wextra -Werror
endif

ifdef ASAN
CFLAGS = -g3 -Wall -Wextra -Werror -fsanitize=address
endif

# Setting variables depending on Operating System
ifdef __LINUX__
	LINKS = -Lmlx_linux -lmlx -lXext -lX11 -lm -lz
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
				parse_texture.c \
				parse_colour.c \
				parse_map.c \
				checks/check_data_completeness.c \
				checks/check_map.c \
				utils/parse_init.c \
				utils/parser_free.c \
				utils/parser_utils.c \
				utils/parse_print.c

INC_PARSER = 	parser.h \
				parse_main.h \
				parse_data.h \
				parse_texture.h \
				parse_colour.h \
				parse_map.h \
				checks/check_data_completeness.h \
				checks/check_map.h \
				utils/parse_init.h \
				utils/parser_utils.h \
				utils/parser_free.h \
				utils/parse_print.h

DIR_RAYCASTER = raycaster
SRC_RAYCASTER = raycaster_main.c \
				utils/raycaster_init.c \
				hooks.c \
				checks.c \
				utils/maths.c \
				intersections.c \
				cast_rays.c \
				utils/raycaster_print.c \
				map_to_3d_textured.c \
				gameplay.c \
				load_xpm.c \
				utils/raycaster_free.c \
				utils/raycaster_utils.c

INC_RAYCASTER = raycaster.h \
				raycaster_main.h \
				utils/raycaster_init.h \
				hooks.h \
				checks.h \
				utils/maths.h \
				intersections.h \
				cast_rays.h \
				utils/raycaster_print.h \
				map_to_3d_textured.h \
				gameplay.h \
				load_xpm.h \
				utils/raycaster_free.h \
				utils/raycaster_utils.h

# Headerfiles
HEADER_FILES = incl/cub3d.h $(DIR_PARSER)/$(INC_PARSER) $(DIR_RAYCASTER)/$(INC_RAYCASTER)

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

.PHONY = all clean fclean re
