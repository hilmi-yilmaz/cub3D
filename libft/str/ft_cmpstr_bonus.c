/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cmpstr_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/10 17:49:26 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/10 12:58:06 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
** The ft_cmpstr function compares the two strings.
**
** Arguments:
**		(char *)	s1: the first string to compare.
**		(char *)	s2: the second string to compare.
**
** Returns:
**		(int)		1 if strings are equal, 0 if not.
*/

int	ft_cmpstr(char *s1, char *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (s1_len != s2_len)
		return (0);
	while (*(s1 + i) != '\0')
	{
		if (*(s1 + i) != *(s2 + i))
			return (0);
		i++;
	}
	return (1);
}
