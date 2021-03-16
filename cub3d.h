#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_img
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;

	int		win_width;
	int		win_height;

	int		img_pos_x;
	int		img_pos_y;

	int		bits_per_pixel;
	int		line_size;
	int		endian;
}			t_img;

void    my_pixel_put(t_img *img, int pos_x, int pos_y, unsigned int colour);
void    draw_horizontal_line(t_img *img, int win_width, int win_height);
void    draw_vertical_line(t_img *img, int win_width, int win_height);
int		argb_to_hex(int t, int r, int g, int b);
int 	key_hook(int keycode, t_img *img);
int 	close(int keycode, t_img *img);
void    draw_x(t_img *img, int x, int y, int win_width, int win_height);
void    draw_box(t_img *img, int x, int y, int box_width, int box_height);
int 	move(int keycode, t_img *img);
#endif