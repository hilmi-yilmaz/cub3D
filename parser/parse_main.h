/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_main.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/17 17:00:35 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/17 17:00:36 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_MAIN_H
# define PARSE_MAIN_H

/* System headers */
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

/* User defined headers */
# include "parser.h"
# include "parse_data.h"
# include "checks/check_data_completeness.h"
# include "checks/check_map.h"
# include "utils/parse_init.h"
# include "utils/parser_utils.h"
# include "utils/parser_free.h"

/* Function prototypes */
int	parse_main(t_parse *parse, char **argv);

#endif