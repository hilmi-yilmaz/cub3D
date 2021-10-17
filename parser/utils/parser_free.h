/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_free.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:05:02 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:05:09 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_FREE_H
# define PARSER_FREE_H

/* System headers */
# include <stdlib.h>

/* User defined headers */
# include "../parser.h"

/* Function prototypes */
void	free_parse(t_parse *parse);
void	free_textures(t_parse *parse);
void	free_map(char **map);
void	*free_2d_str_array_if_fails(char **copy, int i);

#endif