#ifndef CUB3D_H
# define CUB3D_H

/* Parser */
# define UNINIT -1	/* Uninitialized value */


# ifdef __linux__
#  include "mlx_linux/mlx.h"
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define RIGHT_KEY 65363
#  define LEFT_KEY 65361
#  define A_KEY 97
#  define D_KEY 100
#  define W_KEY 119
#  define S_KEY 115
#  define ESC_KEY 65307
# else
#  include "mlx/mlx.h"
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define A_KEY 0
#  define D_KEY 2
#  define W_KEY 13
#  define S_KEY 1
#  define ESC_KEY 53
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

# define STACK_MAX 10000

# define TRUE 1
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

typedef struct s_parse
{
    int     		win_width;
    int     		win_height;
    char    		*north_text;
    char    		*south_text;
    char    		*west_text;
    char    		*east_text;
    int             floor_colour[RGB_DATA_COUNT];
    int             ceiling_colour[RGB_DATA_COUNT];
	char			**map;
}			t_parse;

typedef struct s_recursion_management
{
	unsigned int	i;
	unsigned int	total_recursions;
	char			max_stack_reached;
	int				save_x;
	int				save_y;
	char			error;

}	t_recursion_management;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	
}				t_mlx;

typedef struct s_img
{
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
	t_mlx	mlx;
	t_img	main;		// which will be pushed to  the window
	t_img	north_xpm;
	t_img	south_xpm;
	t_img	west_xpm;
	t_img	east_xpm;
	t_img	scaled_xpm;

}			t_images;

typedef struct s_tmpscale
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

}			t_tmpscale;

typedef struct s_scale
{
	double	f;
	double	fstep;
	double	fi;
	double	s1;
	double	s2;
	int		start;
	int		end;
	double	dev1;
	double	dev2;
	double	d;
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
    t_ray           *hor_ray;
    t_ray           *ver_ray;
	char			*hor_or_ver_intersect; // 'h' or 'v'
    double          *rays_array;	// contains screen_width elements which are distances
    char            *side;			// contains screen_width elements which are either N,S,E,W
	
}	                t_player;

typedef struct s_mlx_key_handler
{
	char	a_key;
	char	w_key;
	char	s_key;
	char	d_key;
	char	left_key;
	char	right_key;
}	t_mlx_key_handler;

typedef struct s_data
{
	t_parse				parse;
	t_images			images;
	t_player			player;
	t_mlx_key_handler	key_handler;

}	t_data;

/* ------------------------------------ PARSING ---------------------------------- */
/* parse_main.c */
int     parse_main(t_parse *parse, char **argv);

/* init.c */
void	parse_init(t_parse *parse);
void	recursion_management_init(t_recursion_management *rec_man);

/* parse_data.c */
int  	parse_data(int fd, t_parse *parse);
int 	decision(int fd, t_parse *parse, char *line);

/* parse_resolution.c */
int   	parse_resolution(int *win_width, int *win_height, char *line);

/* parse_textures.c */
int 	parse_textures(t_parse *parse, char *line);
int    	fill_texture(char **texture, char *line, char *text_id);

/* parse_colour.c */
int     parse_colour(int *colour_array, char *line);
int		fill_colour(int *colour_array, char *line);

/* parse_map.c */
int    	parse_map(int fd, t_parse *parse, char *line);
char  	**create_map(t_parse *parse, char *line, int rows);
int    	old_to_new_map(t_parse *parse, char **new_map, int rows);

/* checks.c */
int     check_resolution(char *line);
int 	check_map(char **map);
int		check_data_completeness(t_parse *parse);

/* print.c */
void    print_parse(t_parse *parse);
void    print_map(char **map);

/* error.c */
int		error_colour(void);
void    *error_malloc(void);

/* utils.c */
int     skip_chr(char *str, int c);
void    find_player_location(int *x, int *y, char **map);
char 	**copy_map(char **map);

/* flood_fill.c */
int 	flood_fill(int x, int y, char **map, t_recursion_management *rec_man);

/* free_data.c */
void    free_parse(t_parse *parse);
void	free_textures(t_parse *parse);
void	free_map(char **map);

/* --------------------------- Raycasting ---------------------------- */

/* raycaster_main.c */
int     raycaster_main(t_data *data);

/* init_data.c */
void	raycaster_init(t_data *data);
void	images_init(t_images *images);
void	player_init(t_player *player, int width);
void	ray_init(t_ray *ray);

/* gameplay.c */
int		gameplay(t_data *data);

/* intersections.c */
int 	horizontal_intersection(t_player *player, double angle, char **map, int i);
int		vertical_intersection(t_player *player, double angle, char **map, int i);
int		expand_ray(t_ray *ray, char **map, double angle, int (*angle_direction)(double));

/* cast_rays.c */
int 	cast_all_rays(t_player *player, t_parse *parse);

/* map_to_3d_untextured.c */
int     map_to_3d_untextured(t_data *data);

/* map_to_3d_textured.c */
int		map_to_3d_textured(t_data *data);

/* utils.c */
void    		ft_swap_doubles(double *x, double *y);
int 			*width_of_accumulated_walls(t_player *player, t_parse *parse);
int 			*width_of_wall(int *which_wall, int width);
int 			amount_visible_walls(int *which_wall, int width);
void    		set_start_location(t_player *player, char **map);
int				ft_arrlen(char **arr);
int     		ft_int_array_len(int *arr);
int				close_window(t_data *data);
void            my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour);
unsigned int    my_pixel_get(t_img *img, int pos_x, int pos_y);
unsigned int 	argb_to_hex(int a, int r, int g, int b);
int             get_argb(unsigned int argb, char c);
void    draw_line_on_wall_edges(t_img *main, int *width_walls, int win_height);


/* free_data.c */
void    free_all(t_data *data);
void    free_images(t_images *images);
void    free_player(t_player *player);

/* Hooks */
//int     hooks(int keycode, t_data *data);
int 	keypress_hook(int keycode, t_data *data);
int 	keyrelease_hook(int keycode, t_data *data);
int     move(t_player *player, double x_local, double y_local, char **map);

/* Checks*/
int     check_wall(char **map, double x, double y);
int     check_coordinates(double x, double y, char **map);
void    check_directions(t_player *player, char **map);
int		check_next_step(double new_x, double new_y, char **map);

/* Draw elements */
void    clear_screen(t_img *main, int win_width, int win_height);
void    draw_columns(t_img *img, int column, int wall_height, int win_height, unsigned int colour);
void    draw_texture(t_img *main, int column, int wall_height, int win_height, unsigned int *colour);
void    draw_floor_ceiling(t_img *main, t_parse *parse);

/* Intersection */
//double	cast_single_ray(t_player *player, double angle, char **map, int i, t_parse *parse);
//int 	cast_all_rays(t_player *player, int width, char **map, t_parse *parse);

/* Map to 3D */
void    map_to_3d(t_data *data);
void    v1_map_to_3d(t_data *data);
void    get_column_xpm(t_img *xpm_img, unsigned int *column_rgb, int column);

/* Math utils */
double	calculate_ray_len(t_player *player, double x, double y);
void    reset_angle(double *angle);
int     unit_circle_upper_lower(double angle);
int     unit_circle_left_right(double angle);
double	deg2rad(double degree);
void	rotate_vector(double *x, double *y, double angle);
double	ft_floor(double x);

/* Printing data */
void    print_wall_x_starts(t_player *player, t_parse *parse);
void    print_intersections(t_player *player, int width);
void    print_ray_data(t_ray ray);
void    print_rays_array(double *rays_array, int width);
void    print_side_array(int *side_array, int width);
void    print_columns(unsigned int *arr, int len);

/* --------------------------- Texture Handling ---------------------------- */

//void    scale_bmp(t_img *xpm_img, t_img *scaled_xpm_img, int xpm_width, int xpm_height, int scaled_xpm_width, int scaled_xpm_height);
void    scale_column(t_img *scaled_xpm, int column, unsigned int *dst, int dst_height);
void    scale_bmp_all_rows(t_img *xpm_img, t_img *scaled_xpm);
void    scale_bmp_single_row(t_img *xpm_img, t_img *scaled_xpm, t_scale *scale_params, int row);
int    	load_all_xpm_images(t_images *images, t_parse *parse);
int    	load_xpm_image(void *mlx_ptr, t_img *xpm_img, char *path);

void			get_scale_params_x(t_tmpscale *scale_params, t_img *xpm, int width);
void			get_scale_params_y(t_tmpscale *scale_params, t_img *xpm, int height);
unsigned int	get_texture_pixel(t_img *xpm, t_tmpscale *scale_params, int dest_x, int dest_y);
void			pixel_from_xpm_to_window(t_img *img, t_img *xpm, t_tmpscale *scale_params, int x_screen, int x, int y, int win_height, t_player *player, int *width_walls, int i, int wall_x, int width);

#endif
