/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:13:07 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/27 18:22:44 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line/get_next_line.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	valid_extensions(char *file)
{
	char	*ext;

	ext = ft_substr(file, ft_strlen(file) - 4, 4);
	if (ft_strncmp(".ber", ext, 4) == 0)
	{
		free(ext);
		return (1);
	}
	free(ext);
	return (0);
}
