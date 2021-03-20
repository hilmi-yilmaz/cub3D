#ifndef CUB3D_H
# define CUB3D_H

# ifdef IS_LINUX
#  include "mlx_linux/mlx.h"
#  include <X11/X.h>
#  define UP_KEY 65362
#  define DOWN_KEY 65364
#  define RIGHT_KEY 65363
#  define LEFT_KEY 65361
# else
#  include "mlx/mlx.h"
#  define UP_KEY 126
#  define DOWN_KEY 125
#  define RIGHT_KEY 124
#  define LEFT_KEY 123
#  define KeyPress 2
#  define KeyPressMask 1L<<0
#  define NoEventMask 1L<<0
#  define DestroyNotify 17
#  define StructureNotifyMask 1L<<17
# endif

typedef struct s_square
{
	int	width;
	int	height;
	int	pos_x;
	int	pos_y;
}			t_square;

typedef struct s_img
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;

	int		win_width;
	int		win_height;

	int		bits_per_pixel;
	int		line_size;
	int		endian;

	unsigned int		floor_colour;
	unsigned int		ceiling_colour;

	t_square square;
}			t_img;


void    my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour);
void    draw_horizontal_line(t_img *img, int win_width, int win_height);
void    draw_vertical_line(t_img *img, int win_width, int win_height);
unsigned int		argb_to_hex(int a, int r, int g, int b);
int 	key_hook(int keycode, t_img *img);
int 	close(int keycode, t_img *img);
void    draw_x(t_img *img, int x, int y, int win_width, int win_height);
void    draw_box(t_img *img, int x, int y, int box_width, int box_height);
int 	move(int keycode, t_img *img);


void    put_square(t_img *img);
int close_window(t_img *img);
int key_input(int keycode, t_img *img);
void reset_image(t_img *img);

void    set_ceiling(t_img *img);
void    set_floor(t_img *img);

void    put_circle(t_img *img);

#endif