/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 17:11:32 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/20 14:04:56 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_remains
{
	int			i;
	char		rest[BUFFER_SIZE];
}				t_remains;

int				get_next_line(int fd, char **line);
char			*create(char *line, char *buff, t_remains *re);
void			oldline_to_line(char *array, char *line);
int				rest_to_line(char *line, char *buff, t_remains *re, int flag);
void			buff_to_line_and_rest(char *line, char *buff, t_remains *re);
int				ft_strchr_mod(char *s, int c);
int				ft_strlen_mod(char *s, int c);
void			set_values(char *buff, int *flag, int *size);

#endif
