/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_texture.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 16:23:10 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 16:23:12 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TEXTURE_H
# define PARSE_TEXTURE_H

/* System headers */
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <errno.h>

/* User defined headers */
# include "../libft/libft.h"
# include "parser.h"

/* Function prototypes */
int	parse_textures(t_parse *parse, char *line);

#endif