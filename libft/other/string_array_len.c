/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_array_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/18 09:30:33 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/10/18 09:30:34 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_str_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (*(arr + i) != NULL)
		i++;
	return (i);
}
