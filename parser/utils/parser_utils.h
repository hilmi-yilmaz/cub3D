/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:04:47 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/19 10:58:21 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

/* System headers */
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

/* User defined headers */
# include "../../libft/libft.h"
# include "parser_free.h"

/* Function prototypes */
int		find_player_location(int *x, int *y, char **map);
char	**copy_map(char **map);

#endif