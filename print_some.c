/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:39:14 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/15 19:50:06 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_printf_s(char *s)
{
	size_t	i;
	char	c;

	i = 0;
	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			return ;
	}
	while (*(s + i))
	{
		c = *(s + i);
		write(1, &c, 1);
		i++;
	}
}

void	ft_printf_d(long long n)
{
	int		i;
	char	c[12];

	i = 0;
	if (n < 0)
	{
		c[0] = '-';
		write(1, &c, 1);
		n *= -1;
	}
	while (n >= 10)
	{
		c[i] = (n % 10) + 48;
		n /= 10;
		i++;
	}
	c[i] = (n % 10) + 48;
	while (i >= 0)
	{
		write(1, &c[i], 1);
		i--;
	}
	c[0] = '\n';
	write(1, &c, 1);
}
