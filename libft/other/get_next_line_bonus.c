/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 17:08:31 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/20 13:59:45 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

/*
** The get_next_line-function uses the helper function to read a line
** from a file descripter and stores the result in *line.
** First some variables are set:
** --> flag is used to indicate whether a newline is found and stops the
** while loop.
** --> *line is set to NULL.
** --> size is set to BUFFER_SIZE. This is done because size needs to be
** initialized even if we don't read, because we have \n in our remainder.
** --> Also, if no data is read, buff[0] = '\0'. No data is read when there
** is a \n in rest.
** --> re[1024]. This is an array of structs. Each element (struct) of the
** array is keeping track of the remainder of a specific file descriptor.
** 1024 is chosen because a process on a Linux system has a limit of 1024 file
** descriptor.
** ------------------------------------------------------------------------
** Then, the data is read and the other functions are being called to
** fill *line.
*/

int	get_next_line(int fd, char **line)
{
	int					size;
	int					flag;
	char				buff[BUFFER_SIZE + 1];
	static t_remains	re[1024];

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	*line = NULL;
	set_values(buff, &flag, &size);
	while (flag == 0)
	{
		if (ft_strchr_mod(re[fd].rest + re[fd].i, '\n') == 0)
			size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
			return (-1);
		buff[size] = '\0';
		*line = create(*line, buff, &re[fd]);
		if (*line == NULL)
			return (-1);
		flag = rest_to_line(*line, buff, &re[fd], flag);
		buff_to_line_and_rest(*line, buff, &re[fd]);
		if (size == 0)
			return (0);
	}
	return (1);
}

/*
** The create-function allocates exactly enough memmory for *line.
** It also fill line with old line, in case of BUFFERS_SIZE being
** smaller than the length of the line.
*/

char	*create(char *line, char *buff, t_remains *re)
{
	int		size;
	char	*array;

	size = ft_strlen_mod(line, '\0') + ft_strlen_mod(buff, '\n') \
			 + ft_strlen_mod(re->rest + re->i, '\n');
	array = (char *)malloc(sizeof(char) * size + 1);
	if (array == NULL)
		return (NULL);
	*(array + 0) = '\0';
	*(array + size) = '\0';
	oldline_to_line(array, line);
	return (array);
}

/*
** The oldline_to_line-function is used in the create-function
** to fill line with oldline
** in the case of BUFFER_SIZE being smaller than the length of the line
*/

void	oldline_to_line(char *array, char *line)
{
	int	i;

	if (line == NULL)
		return ;
	i = 0;
	while (*(line + i) != '\0')
	{
		*(array + i) = *(line + i);
		i++;
	}
	*(array + i) = '\0';
	free(line);
}

/*
** The rest_to_line-function fills line with rest if rest is not empty
** Each time a character from rest is transferred to line
** that character is converted to a \0 in rest.
** Also the i variable of the struct is used to remember the offset
** For example:
** re->rest = [h i l m i \n y i l m a z \0 \0 \0]
** After this function, rest looks like this:
** re->rest = [\0 \0 \0 \0 \0 \0 y i l m a z \0 \0 \0]
** re->i = 6.
*/

int	rest_to_line(char *line, char *buff, t_remains *re, int flag)
{
	int	i;
	int	len_line;

	i = 0;
	flag = ft_strchr_mod(buff, '\n') + ft_strchr_mod(re->rest + re->i, '\n');
	len_line = ft_strlen_mod(line, '\0');
	while (i < BUFFER_SIZE)
	{
		if (*(re->rest + re->i + i) == '\n')
		{
			*(re->rest + re->i + i) = '\0';
			re->i = re->i + i + 1;
			break ;
		}
		else if (*(re->rest + re->i + i) == '\0')
		{
			re->i = 0;
			break ;
		}
		*(line + len_line + i) = *(re->rest + re->i + i);
		*(re->rest + re->i + i) = '\0';
		i++;
	}
	*(line + len_line + i) = '\0';
	return (flag);
}

/*
** The buff_to_line_and_rest-function fills line with buff.
** The remainder of buff is added to rest if needed.
*/

void	buff_to_line_and_rest(char *line, char *buff, t_remains *re)
{
	int	i;
	int	j;
	int	len_line;

	i = 0;
	j = 0;
	len_line = ft_strlen_mod(line, '\0');
	while (*(buff + i) != '\0' && *(buff + i) != '\n')
	{
		*(line + len_line + i) = *(buff + i);
		i++;
	}
	*(line + len_line + i) = '\0';
	while (i < BUFFER_SIZE && *(buff + i) != '\0')
	{
		*(re->rest + re->i + j) = *(buff + i + 1);
		i++;
		j++;
	}
}
