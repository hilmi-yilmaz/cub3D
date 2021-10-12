/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 11:16:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/12 13:34:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

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
