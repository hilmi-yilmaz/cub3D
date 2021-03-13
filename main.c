/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/13 12:20:02 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/13 19:50:34 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include <stddef.h>

int main(void)
{
    void    *mlx_ptr;
    void    *win_ptr;

    mlx_ptr = mlx_init();
    if (mlx_ptr == NULL)
        return (1);
    win_ptr = mlx_new_window(mlx_ptr, 800, 400, "Test");
    mlx_loop(mlx_ptr);
    return (0);
}