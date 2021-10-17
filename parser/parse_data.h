/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_data.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:00:25 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:00:26 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_DATA_H
# define PARSE_DATA_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>

/* User defined headers */
# include "../libft/libft.h"
# include "parser.h"
# include "parse_texture.h"
# include "parse_colour.h"
# include "parse_map.h"

/* Function prototypes */
int	parse_data(int fd, t_parse *parse);

#endif