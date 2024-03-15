/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:31:37 by minkylee          #+#    #+#             */
/*   Updated: 2023/07/27 18:23:48 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include "so_long.h"

void	free_some(t_game *game, t_param *param, t_image *image, int flag)
{
	int	i;

	i = 0;
	if (flag == 1)
	{
		while (i < game->height)
		{
			free(game->map[i]);
			free(game->visit[i++]);
		}
		free(game->map);
		free(game->visit);
	}
	else if (flag == 2)
	{
		while (i < game->height)
			free(game->map[i++]);
		free(game->map);
	}
	free(game);
	free(param);
	free(image);
}

void	draw_map(t_param *param, t_game *game)
{
	int	hei;
	int	wid;

	hei = 0;
	while (hei < game->height)
	{
		wid = 0;
		while (wid < game->width)
		{
			print_image(param, '0', wid, hei);
			print_image(param, game->map[hei][wid], wid, hei);
			wid++;
		}
		hei++;
	}
}

int	is_valid_game(char *file, t_game *game, t_param *param, t_image *image)
{
	int	count;
	int	fd;

	if (!valid_extensions(file))
	{
		free_some(game, param, image, 0);
		ft_printf_s("Invalid extension\n");
		return (0);
	}
	count = count_row(file);
	fd = open(file, O_RDONLY);
	if (!parse_map(fd, game, count))
	{
		ft_printf_s("Failed to load map\n");
		free_some(game, param, image, 0);
		return (0);
	}
	close(fd);
	init_structure(game, param, image);
	if (!found_some(game, param))
	{
		ft_printf_s("invalid map\n");
		return (0);
	}
	return (1);
}

void	start_game(t_game *game, t_param *param, t_image *image)
{
	int	i;

	i = 0;
	game->mlx = mlx_init();
	game->win = mlx_new_window(\
		game->mlx, game->width * 64, game->height * 64, "my_mlx");
	mlx_key_hook(game->win, handle_key_event, param);
	mlx_hook(game->win, KEY_X_BUTTON, 0, end_game, param);
	init_image(image, game);
	draw_map(param, game);
	while (i < game->height)
	{
		free(game->visit[i]);
		i++;
	}
	free(game->visit);
	game->visit = NULL;
	init_visit(game);
	update_game(game, param);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	*game;
	t_param	*param;
	t_image	*image;

	if (argc != 2)
		return (0);
	game = (t_game *)malloc(sizeof(t_game));
	param = (t_param *)malloc(sizeof(t_param));
	image = (t_image *)malloc(sizeof(t_image));
	if (!game || !param || !image)
	{
		ft_printf_s("Error: Memory allocation failed.\n");
		free_some(game, param, image, 0);
		exit(0);
	}
	if (!is_valid_game(argv[1], game, param, image))
	{
		ft_printf_s("Error: Invalid game.\n");
		exit(0);
	}
	start_game(game, param, image);
	free_some(game, param, image, 2);
	return (0);
}
