/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nblen_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: hyilmaz <hyilmaz@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/08 18:13:02 by hyilmaz       #+#    #+#                 */
/*   Updated: 2021/03/10 12:54:16 by hyilmaz       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_nblen function calculates the length of a number based
** on a given base.
** E.g. 3869 with base 10 has a length of 4 (4 digits).
**
** Arguments:
**		(long)	nb: the input number.
**		(int)	base: the base for which to calculate the length.
**
** Returns:
**		(int)	i: length of the number
*/

int	ft_nblen(long nb, int base)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}
