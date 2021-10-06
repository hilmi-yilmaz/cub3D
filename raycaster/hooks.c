/* Standard library header files */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

int	keypress_hook(int keycode, t_data *data)
{	
	if (keycode == ESC_KEY)
		close_window(data);
	if (keycode == W_KEY)
		data->key_handler.w_key = 1;
	if (keycode == S_KEY)
		data->key_handler.s_key = 1;
	if (keycode == D_KEY)
		data->key_handler.d_key = 1;
	if (keycode == A_KEY)
		data->key_handler.a_key = 1;
	if (keycode == RIGHT_KEY)
		data->key_handler.right_key = 1;
	else if (keycode == LEFT_KEY)
		data->key_handler.left_key = 1;
	return (0);
}

int	keyrelease_hook(int keycode, t_data *data)
{	
	if (keycode == W_KEY)
		data->key_handler.w_key = 0;
	if (keycode == S_KEY)
		data->key_handler.s_key = 0;
	if (keycode == D_KEY)
		data->key_handler.d_key = 0;
	if (keycode == A_KEY)
		data->key_handler.a_key = 0;
	if (keycode == RIGHT_KEY)
		data->key_handler.right_key = 0;
	else if (keycode == LEFT_KEY)
		data->key_handler.left_key = 0;
	return (0);
}
