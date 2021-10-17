/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:00:46 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:00:47 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAP_H
# define PARSE_MAP_H

/* System headers */
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

/* User defined headers */
# include "../libft/libft.h"
# include "parser.h"
# include "utils/parser_free.h"

/* Function prototypes */
int	parse_map(int fd, t_parse *parse, char **line);

#endif