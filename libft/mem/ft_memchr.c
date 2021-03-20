/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:37:08 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/10 12:49:37 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr_s;

	i = 0;
	ptr_s = s;
	while (i < n)
	{
		if (*(ptr_s + i) == (unsigned char)c)
		{
			return ((void *)ptr_s + i);
		}
		i++;
	}
	return (NULL);
}
