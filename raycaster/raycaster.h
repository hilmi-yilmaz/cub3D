#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "parser/parse.h"

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
	t_img	main;
	t_img	north_xpm;
	t_img	south_xpm;
	t_img	west_xpm;
	t_img	east_xpm;

}			t_images;

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
    double          *rays_array;
    char            *side;
    t_ray           *hor_ray;
    t_ray           *ver_ray;

}	                t_player;

typedef struct 	s_mlx_key_handler
{
	char	a_key;
	char	w_key;
	char	s_key;
	char	d_key;
	char	left_key;
	char	right_key;
}				t_mlx_key_handler;

typedef struct s_data
{
	t_parse				parse;
	t_images			images;
	t_player			player;
	t_mlx_key_handler	key_handler;

}	t_data;

/* raycaster_main.c */
int     raycaster_main(t_data *data);

/* init_data.c */
int		raycaster_init(t_data *data);

/* gameplay.c */
int		gameplay(t_data *data);

/* cast_rays.c */
int 	cast_all_rays(t_player *player, t_parse *parse);

/* intersections.c */
int 	horizontal_intersection(t_player *player, double angle, char **map, int i);
int		vertical_intersection(t_player *player, double angle, char **map, int i);
int		expand_ray(t_ray *ray, char **map, double angle, int (*angle_direction)(double));

/* map_to_3d_untextured.c */
int     map_to_3d_untextured(t_data *data);

/* map_to_3d_textured.c */
void	map_to_3d_textured(t_data *data);

/* utils.c */
void    		*error_malloc(unsigned int bytes);
int				ft_arrlen(char **arr);
int				close_window(t_data *data);
void            my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour);
unsigned int    my_pixel_get(t_img *img, int pos_x, int pos_y);
unsigned int 	argb_to_hex(int a, int r, int g, int b);


/* free_data.c */
void    free_all(t_data *data);
void    free_images(t_images *images);
void    free_player(t_player *player);

/* Hooks */
int 	keypress_hook(int keycode, t_data *data);
int 	keyrelease_hook(int keycode, t_data *data);

/* Checks*/
int     check_wall(char **map, double x, double y);
int     check_coordinates(double x, double y, char **map);
int		check_next_step(double new_x, double new_y, char **map);

/* Draw elements */
void    draw_columns(t_img *img, int column, int wall_height, int win_height, unsigned int colour);
void    draw_floor_ceiling(t_img *main, t_parse *parse);

/* Math utils */
double	calculate_ray_len(t_player *player, double x, double y);
void    reset_angle(double *angle);
int     unit_circle_upper_lower(double angle);
int     unit_circle_left_right(double angle);
double	deg2rad(double degree);
void	rotate_vector(double *x, double *y, double angle);

/* Printing data */
void    print_intersections(t_player *player, int width);
void    print_ray_data(t_ray ray);
void    print_rays_array(double *rays_array, int width);
void    print_side_array(int *side_array, int width);
void    print_columns(unsigned int *arr, int len);

/* --------------------------- Texture Handling ---------------------------- */

int    	load_all_xpm_images(t_images *images, t_parse *parse);
int    	load_xpm_image(void *mlx_ptr, t_img *xpm_img, char *path);

#endif