#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "../parser/parser.h"

# define PI 3.141592653589793
# define FOV 60

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	mlx_ptr_flag;
	char	win_ptr_flag;
}				t_mlx;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	int		width;
	int		height;
	char	img_ptr_flag;
	char	img_addr_flag;
}				t_img;

typedef struct s_ray
{
	double	x;
	double	y;
	double	xa;
	double	ya;
	char	error;
}				t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	speed;
	double	rot_speed;
	double	*rays_array;
	char	*side;
	t_ray	*hor_ray;
	t_ray	*ver_ray;
}				t_player;

typedef struct s_mlx_key_handler
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
	t_player			player;
	t_mlx_key_handler	key_handler;
	t_mlx				mlx;
	t_img				main;
	t_img				north_xpm;
	t_img				south_xpm;
	t_img				west_xpm;
	t_img				east_xpm;
}				t_data;

#endif