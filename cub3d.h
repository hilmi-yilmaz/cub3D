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
#  define W_KEY 119
#  define S_KEY 115
# else
#  define IS_LINUX 0
#  include "mlx/mlx.h"
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define A_KEY 0
#  define D_KEY 2
#  define W_KEY 13
#  define S_KEY 1
// #  define KeyPress 2
// #  define KeyPressMask 1L<<0
// #  define NoEventMask 1L<<0
// #  define DestroyNotify 17
// #  define StructureNotifyMask 1L<<17
# endif

/* If not defined, we are on OSX */
# ifndef __linux__
#  define __linux__ 0
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

# define UNINITIALIZED -1 /* Rename to UNINIT */

# define TRUE 1				/* Create a typedef for this */
# define FALSE 0

# define UNIT 1
# define EDGE 1
# define INF 2147483647 

#define GLASS 0.1

# define XY_COORDINATES 2

# define PI 3.141592653589793

# define FOV 60

# define WALL_RATIO 2

# define INF 2147483647

# define INF_SMALL 0.0000000000001

typedef struct s_img
{
    void            *mlx_ptr;
    void            *win_ptr;
    void            *img_ptr;
    char            *img_addr;

    int             bits_per_pixel;
    int             line_size;
    int             endian;

	int				width;
	int				height;

}                   t_img;

typedef struct s_images
{
	t_img	main;
	t_img	north_xpm;
	t_img	south_xpm;
	t_img	west_xpm;
	t_img	east_xpm;

}			t_images;

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

}	t_parse;

typedef struct s_scale
{
	double	fx;
	double	fy;
	double	fxstep;
	double	fystep;
	double	fix;
	double	fiy;
	double	sy1;
	double	sy2;
	int		jstart;
	int		jend;
	double	devY1;
	double	devY2;
	double	sx1;
	double	sx2;
	int		istart;
	int		iend;
	double	devX1;
	double	devX2;
	double	dx;
	double	dy;
	double	AP;
	double	destR;
	double	destG;
	double	destB;
	int		sR;
	int		sG;
	int		sB;

}			t_scale;

typedef struct s_ray
{
    double  x;
    double  y;
    double  xa;
    double  ya;
    int     error;  

}               t_ray;

typedef struct s_player
{
	double        	x;
	double        	y;
    double          angle;
    double        	speed;
    double         	rot_speed;
    t_ray           hor_ray;
    t_ray           ver_ray;
    double          *rays_array;
    char            *side;
	int				*which_wall;
	
}	                t_player;

typedef struct s_data
{
	t_parse		parse;
	t_images	images;
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

/* --------------------------- V1 Raycasting ---------------------------- */
int     raycaster_main(t_data *data);

/* Initialize */
void    init(t_data *data);
void    find_start_location(t_player *player, char **map);
void    set_start_location(t_player *player, char **map, int i, int j);

/* Hooks */
int     hooks(int keycode, t_data *data);
int     move(t_player *player, double x_local, double y_local, char **map);

/* Checks*/
int     check_wall(char **map, double x, double y);
int     check_coordinates(double x, double y, char **map);
void    check_directions(t_player *player, char **map);
int		check_next_step(double new_x, double new_y, char **map);

/* Draw elements */
void    clear_screen(t_img *img, int win_width, int win_height);
void    draw_columns(t_img *img, int column, int wall_height, int win_height, unsigned int colour);
void    draw_floor_ceiling(t_img *main, t_parse *parse);

/* Intersection */
int 	horizontal_intersection(t_player *player, double angle, char **map);
int		vertical_intersection(t_player *player, double angle, char **map);
int		expand_ray(t_ray *ray, char **map, double angle, int (*angle_direction)(double));
double	cast_single_ray(t_player *player, double angle, char **map, int i);
int 	cast_all_rays(t_player *player, int width, char **map);

/* Map to 3D */
void    map_to_3d(t_img *main, t_player *player, int win_width, int win_height);
void    v1_map_to_3d(t_images *images, t_player *player, t_parse *parse);
int 	*width_of_wall(int *which_wall, int width);
int 	amount_visible_walls(int *which_wall, int width);
void    get_column_xpm(t_img *xpm_img, unsigned int *column_rgb, int column);

/* Math utils */
double	calculate_ray_len(t_player *player, double x, double angle);
double	calculate_ray_len_v1(t_player *player, double x, double y);
void    reset_angle(double *angle);
int     unit_circle_upper_lower(double angle);
int     unit_circle_left_right(double angle);
double	deg2rad(double degree);
void	rotate_vector(double *x, double *y, double angle);

/* MLX utils */
int				close_window(t_data *data);
void            my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour);
unsigned int    my_pixel_get(t_img *img, int pos_x, int pos_y);
unsigned int 	argb_to_hex(int a, int r, int g, int b);
int             get_argb(unsigned int argb, char c);

/* To libft */
int		ft_arrlen(char **arr);

/* Printing data */
void    print_ray_data(t_ray ray);
void    print_rays_array(double *rays_array, int width);
void    print_side_array(int *side_array, int width);

/* --------------------------- Texture Handling ---------------------------- */

void    scale_bmp(t_img *xpm_img, t_img *scaled_xpm_img, int xpm_width, int xpm_height, int scaled_xpm_width, int scaled_xpm_height);

void    load_all_xpm_images(t_images *images, t_parse *parse);
void    load_xpm_image(t_img *xpm_img, char *path);

#endif
