/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:09:33 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/27 17:15:34 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line/get_next_line.h"

void	init_visit(t_game *game)
{
	int	n;
	int	m;
	int	i;

	n = 0;
	i = 0;
	game->visit = (char **)malloc(sizeof(char *) * game->height);
	if (game->visit == NULL)
		return ;
	while (n < game->height)
	{
		game->visit[n] = (char *)malloc(sizeof(char) * game->width);
		if (game->visit[n] == NULL)
		{
			while (i < n)
				free(game->visit[i++]);
			free(game->visit);
			game->visit = NULL;
			return ;
		}
		m = 0;
		while (m < game->width)
			game->visit[n][m++] = '0';
		n++;
	}
}

void	init_image(t_image *image, t_game *game)
{
	int	img_width;
	int	img_height;

	image->img_grass = mlx_xpm_file_to_image(\
		game->mlx, "./images/grass.xpm", &img_width, &img_height);
	image->img_coin = mlx_xpm_file_to_image(\
		game->mlx, "./images/coin.xpm", &img_width, &img_height);
	image->img_exit = mlx_xpm_file_to_image(\
		game->mlx, "./images/exit.xpm", &img_width, &img_height);
	image->img_hill = mlx_xpm_file_to_image(\
		game->mlx, "./images/Hills.xpm", &img_width, &img_height);
	image->img_player = mlx_xpm_file_to_image(\
		game->mlx, "./images/player.xpm", &img_width, &img_height);
}

void	init_structure(t_game *game, t_param *param, t_image *image)
{
	param->x = -1;
	param->y = -1;
	param->image = image;
	game->exit_x = -1;
	game->exit_y = -1;
	game->coin = 0;
	game->cnt = 0;
	game->exit = 0;
	game->walk_cnt = 0;
	param->game = game;
}
