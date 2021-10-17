/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_print.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:04:21 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:04:21 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_PRINT_H
# define PARSE_PRINT_H

/* System headers */
# include <stdio.h>

/* User defined headers */
# include "../parser.h"

/* Function prototypes */
void	print_parse(t_parse *parse);
void	print_map(char **map);

#endif