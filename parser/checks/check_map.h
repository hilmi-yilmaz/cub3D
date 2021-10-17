/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:06:11 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:06:13 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_MAP_H
# define CHECK_MAP_H

/* System headers */
# include <stdio.h>

/* User defined headers */
# include "../../libft/libft.h"
# include "../parser.h"
# include "../utils/parser_utils.h"
# include "../utils/parse_init.h"

/* Macros */
# define STACK_MAX 10000

/* Function prototypes */
int	check_map(char **map);

#endif