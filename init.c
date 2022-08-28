/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:14:16 by aberneli          #+#    #+#             */
/*   Updated: 2022/05/06 13:42:03 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_parsing(t_data *d)
{
	d->fd = open(d->map_path, O_RDONLY);
	if (d->fd < 0)
		return (print_error(ERR_BADFILE, NULL));
	if (parsing(d) < 0)
	{
		close(d->fd);
		return (-1);
	}
	close(d->fd);
	if (d->debut < 0)
		return (print_error(ERR_EMPTY_MAP, NULL));
	return (0);
}

static int	init_player(t_cub *c, t_data *d)
{
	if (d->pdir == 0)
		return (print_error(ERR_NO_SPAWN, NULL));
	c->p.x = (float)d->px + 0.5;
	c->p.y = (float)d->py + 0.5;
	c->p.dirx = cos(d->pang);
	c->p.diry = sin(d->pang);
	c->p.planex = cos(d->pang + (M_PI / 2));
	c->p.planey = sin(d->pang + (M_PI / 2));
	return (0);
}

static int	init_parse_data(t_cub *c, t_data *d)
{
	if (mapping(d, c, d->map_path) < 0)
		return (-1);
	if (check_map_border(c) < 0)
		return (-1);
	if (parse_color(d, &c->g) < 0)
		return (-1);
	if (init_player(c, d) < 0)
		return (-1);
	return (0);
}

static int	init_mlx(t_cub *c, t_data *d)
{
	c->mlx = mlx_init();
	if (!c->mlx)
		return (print_error(ERR_MLX_FAIL, NULL));
	if (load_xpm(d, c) < 0)
		return (-1);
	c->mlx_win = mlx_new_window(c->mlx, WIN_W, WIN_H, "CUB3D");
	if (!c->mlx_win)
		return (print_error(ERR_MLX_FAIL, NULL));
	c->fb = new_img(c->mlx, WIN_W, WIN_H);
	if (!c->fb)
		return (-1);
	c->fb_swap = new_img(c->mlx, WIN_W, WIN_H);
	if (!c->fb_swap)
		return (-1);
	c->ev = register_events(c->mlx_win);
	if (!c->ev)
		return (print_error(ERR_ALLOC, NULL));
	return (0);
}

int	init_cub(t_cub *c, char *path)
{
	t_data	d;

	ft_memset(c, 0, sizeof(t_cub));
	ft_memset(&d, 0, sizeof(t_data));
	d.map_path = path;
	if (init_parsing(&d) < 0)
		return (clear_data(&d));
	if (init_parse_data(c, &d) < 0)
		return (clear_data(&d));
	if (init_mlx(c, &d) < 0)
		return (clear_data(&d));
	clear_data(&d);
	c->refresh = 1;
	mlx_loop_hook(c->mlx, loop_hook, c);
	mlx_hook(c->mlx_win, 17, (1L << 17), quit_hook, c);
	mlx_loop(c->mlx);
	return (0);
}
