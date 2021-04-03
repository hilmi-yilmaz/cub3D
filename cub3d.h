#ifndef CUB3D_H
# define CUB3D_H

# ifdef IS_LINUX
#  include "mlx_linux/mlx.h"
#  include <X11/X.h>
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define RIGHT_KEY 65363
#  define LEFT_KEY 65361
#  define A_KEY 97
#  define D_KEY 100
# else
#  include "mlx/mlx.h"
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define A_KEY 0
#  define D_KEY 2
#  define KeyPress 2
#  define KeyPressMask 1L<<0
#  define NoEventMask 1L<<0
#  define DestroyNotify 17
#  define StructureNotifyMask 1L<<17
# endif

# include "libft/libft.h"

# define LEN_R 1
# define LEN_NO 2
# define LEN_SO 2
# define LEN_WE 2
# define LEN_EA 2
# define LEN_S 1
# define LEN_F 1
# define LEN_C 1

# define RGB_DATA_COUNT 3
# define RESOLUTION_DATA_COUNT 2
# define MAX_KOMMAS 2

# define UNINITIALIZED -1

# define TRUE 1
# define FALSE 0

# define UNIT 64
# define EDGE 0

typedef struct s_map
{
    int **map;
    int *len_element;
    
}       t_map;

typedef struct s_info
{
    int     win_width;
    int     win_height;

    char    *north_text;
    char    *south_text;
    char    *west_text;
    char    *east_text;

    char    *sprite_text;

    int     floor_colour[RGB_DATA_COUNT];
    int     ceiling_colour[RGB_DATA_COUNT];

    t_map   map;

}                   t_info;

typedef struct s_player
{
	int	x;
	int	y;

	float x_unit;
	float y_unit;

	int width;
	int	height;

	float alpha;
	
}	t_player;

typedef struct s_img
{
    void            *mlx_ptr;
    void            *win_ptr;
    void            *img_ptr;
    char            *img_addr;

    int             bits_per_pixel;
    int             line_size;
    int             endian;

	t_player		player;
	t_info			info;

}                   t_img;


/* Parsing data */
int     parse_main(t_info *info, char **argv);
void    	info_init(t_info *info);
int     	parse_data(int fd, t_info *info);
int     		parse_resolution(int *win_width, int *win_height, char *line);
int     		parse_textures(t_info *info, char *line);
int     			fill_texture(char **texture, char *line, char *text_id);
int     		parse_colour(int *colour_array, char *line);
int     		parse_map(int fd, t_info *info, char *line);
int     			**create_map(t_info *info, char *line, int rows);
int     			*create_len(t_info *info, char *line, int rows);
int     			old_to_new_map(t_info *info, int **new_map, int rows);
int			check_data_completeness(t_info *info);

/* Checks while parsing */
int     check_resolution(char *line);
int		fill_colour(int *colour_array, char *line);
int		error_colour(void);
void    *error_malloc(void);

/* Utils */
int     skip_chr(char *str, int c);

/* Free data */
void    free_info(t_info *info);
void	free_textures(t_info *info);
void	free_map(int **map);
void	free_len_elements(t_map map);


/* Temporary helper functions */
void    print_info(t_info *info);
void    print_map(t_info *info);

/* Raycaster */
int		raycaster_main(t_img *img, t_info *info);

#endif