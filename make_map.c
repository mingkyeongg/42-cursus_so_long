/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:36:10 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/24 19:27:44 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line/get_next_line.h"

int	count_row(char *file)
{
	int		fd;
	int		cnt;
	char	*line;

	fd = open(file, O_RDONLY);
	cnt = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		cnt++;
		free(line);
	}
	close(fd);
	return (cnt);
}

int	join_map(char *line, int *col, t_game *game, int row)
{
	int	length;
	int	i;

	length = ft_strlen(line);
	i = 0;
	if (line[length - 1] == '\n')
		line[length - 1] = '\0';
	if (length > *col)
		*col = length;
	game->map[row] = (char *)malloc(sizeof(char) * (length + 1));
	if (!game->map[row])
	{
		while (i < row + 1)
			free(game->map[i++]);
		free(game->map);
		game->map = NULL;
		return (0);
	}
	ft_strlcpy(game->map[row], line, length + 1);
	return (length);
}

int	parse_map(int fd, t_game *game, int count)
{
	char	*line;
	int		row;
	int		col;
	int		length;

	row = 0;
	col = 0;
	game->map = (char **)malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		return (0);
	game->map[count] = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		length = join_map(line, &col, game, row++);
		if (!length)
			return (0);
		free(line);
	}
	game->height = row;
	game->width = col - 1;
	close(fd);
	return (1);
}
