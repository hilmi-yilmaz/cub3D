/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 16:37:09 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/10 12:50:00 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr_s1;
	const unsigned char	*ptr_s2;

	i = 0;
	ptr_s1 = s1;
	ptr_s2 = s2;
	while (i < n)
	{
		if (*(ptr_s1 + i) != *(ptr_s2 + i))
			return (*(ptr_s1 + i) - *(ptr_s2 + i));
		i++;
	}
	return (0);
}
