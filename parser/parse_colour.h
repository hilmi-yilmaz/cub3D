/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_colour.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:03:33 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:04:05 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COLOUR_H
# define PARSE_COLOUR_H

/* System headers */
# include <stdio.h>

/* User defined headers */
# include "../libft/libft.h"
# include "parser.h"

/* Function prototypes */
int	parse_colour(t_parse *parse, char *line);

#endif