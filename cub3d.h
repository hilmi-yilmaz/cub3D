#ifndef CUB3D_H
# define CUB3D_H

# ifdef IS_LINUX
#  include "mlx_linux/mlx.h"
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define RIGHT_KEY 65363
#  define LEFT_KEY 65361
#  define A_KEY 97
#  define D_KEY 100
# else
#  define IS_LINUX 0
#  include "mlx/mlx.h"
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define A_KEY 0
#  define D_KEY 2
// #  define KeyPress 2
// #  define KeyPressMask 1L<<0
// #  define NoEventMask 1L<<0
// #  define DestroyNotify 17
// #  define StructureNotifyMask 1L<<17
# endif

# include "incl/X.h"
# include "libft/libft.h"

# define LEN_R 1	/* Rename to OFFSET_R */
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

# define UNINITIALIZED -1 /* Rename to UNINT */

# define TRUE 1				/* Create a typedef for this */
# define FALSE 0

# define UNIT 64
# define EDGE 1

# define XY_COORDINATES 2

# define PI 3.1415

# define FOV 30 /* in degrees */

// typedef struct s_map
// {
//     int **map;
//     int *len_element;
    
// }       t_map;

// typedef struct s_info
// {
//     int     win_width;
//     int     win_height;

//     char    *north_text;
//     char    *south_text;
//     char    *west_text;
//     char    *east_text;

//     char    *sprite_text;

//     int     floor_colour[RGB_DATA_COUNT];
//     int     ceiling_colour[RGB_DATA_COUNT];

//     t_map   map;

// }                   t_info;

typedef struct s_parse
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

	char	**map;
	//int		*map_len;

}	t_parse;

typedef struct s_img
{
    void            *mlx_ptr;
    void            *win_ptr;
    void            *img_ptr;
    char            *img_addr;

    int             bits_per_pixel;
    int             line_size;
    int             endian;

}                   t_img;

typedef struct s_player
{
	/* These are pixel coordinates of the player */
	int	x;			/* 128 */
	int	y;			/* 192 */

	/* These are unit coordinates of the player */
	float x_unit;	/*	128 / UNIT	*/
	float y_unit;	/* 	192 / UNIT 	*/

	int width;
	int	height;

	float angle;

    int *rays_array;
	
}	t_player;

typedef struct s_data
{
	t_parse		parse;
	t_img	    img;
	t_player	player;

}	t_data;

/* ------------------------------------ PARSING ---------------------------------- */
/* Parsing data */
int     parse_main(t_parse *parse, char **argv);
void    	parse_init(t_parse *parse);
int     	parse_data(int fd, t_parse *parse);
int     		parse_resolution(int *win_width, int *win_height, char *line);
int     		parse_textures(t_parse *parse, char *line);
int     			fill_texture(char **texture, char *line, char *text_id);
int     		parse_colour(int *colour_array, char *line);
int     		parse_map(int fd, t_parse *parse, char *line);
char     			**create_map(t_parse *parse, char *line, int rows);
int     			*create_len(t_parse *parse, char *line, int rows);
int     			old_to_new_map(t_parse *parse, char **new_map, int rows);
int			check_data_completeness(t_parse *parse);

/* Checks while parsing */
int     check_resolution(char *line);
int		fill_colour(int *colour_array, char *line);
int		error_colour(void);
void    *error_malloc(void);

/* Utils */
int     skip_chr(char *str, int c);

/* Free data */
void    free_parse(t_parse *parse);
void	free_textures(t_parse *parse);
void	free_map(char **map);
void	free_map_len(int *map_len);


/* Temporary helper functions */
void    print_parse(t_parse *parse);
void    print_map(t_parse *parse);

// /* ------------------------------------ CASTING ---------------------------------- */
// int		raycaster_main(t_data *data);

// void	init(t_data *data);
// void	set_start_location(char **map, int *x, int *y, float *alpha);
// void	player_location(t_player *player);

// void	draw_player(t_img *img, t_player *player);
// void	remove_current_player(t_img *img, t_player *player);

// void	draw_unit(t_img *img, int pos_x, int pos_y);
// void	draw_map(t_img *img, char **map);
// void	draw_line(t_img *img, t_player *player, float angle, int len);
// void	remove_line(t_img *img, t_player *player, float angle, int len);

// int		check_wall(char **map, int x, int y); /* x and y are pixel coordinates */

// double	calculate_ray_len(t_player player, int x, int y);
// int     expand_ray(t_data *data, int *xy_coordinates, float xa, float ya);

// int		*intersection(t_img *img, float angle);
// int 	horizontal_intersection(t_data *data, float angle, int *horizontal);
// int		vertical_intersection(t_data *data, float angle, int *vertical);
// int		draw_point(t_img *img, int x, int y);
// int		unit_circle_upper_lower(float alpha);
// int		unit_circle_left_right(float alpha);

// int 	cast_single_ray(t_data *data, float angle);
// void    cast_all_rays(t_data *data);
// int 	cast_fov(t_data *data);
// int     remove_cast_fov(t_data *data);

// int		ft_arrlen(char **arr);
// void	print_rays(int *rays_array, int len);

// /* related to mlx */
// int				close_window(t_data *data);
// unsigned int 	argb_to_hex(int a, int r, int g, int b);
// void    		my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour);
// int				key_input(int keycode, t_data *data);

/* --------------------------- v1 Raycasting ---------------------------- */
int     raycaster_main(t_data *data);

/* Initialize */
void    init(t_data *data);
void    find_start_location(t_player *player, char **map);
void    set_start_location(t_player *player, char **map, int i, int j);

/* Drawing elements */
void    draw_unit(t_img *img, int pos_x, int pos_y, unsigned int colour);
void    set_background_color(t_img *img, t_parse *parse, unsigned int colour);
void    draw_map(t_img *img, t_parse *parse);

/* MLX utils */
void            my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour);
unsigned int 	argb_to_hex(int a, int r, int g, int b);

#endif