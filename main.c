/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/21 16:23:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/22 17:59:25 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_info  info;
    int     parse_return;

    parse_return = parse_main(&info, argv);
    if (parse_return == -1)
        return (-1);
    return (0);
}