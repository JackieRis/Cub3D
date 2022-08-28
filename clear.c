/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:14:40 by aberneli          #+#    #+#             */
/*   Updated: 2022/05/06 17:18:39 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	clear_data(t_data *d)
{
	free(d->tmpf);
	free(d->tmpc);
	free(d->no);
	free(d->so);
	free(d->we);
	free(d->ea);
	return (-1);
}

void	clear_gfx(t_gfx *g, void *mlx)
{
	clear_img(g->textures[0], mlx);
	clear_img(g->textures[1], mlx);
	clear_img(g->textures[2], mlx);
	clear_img(g->textures[3], mlx);
}

void	clear_map(t_map *m)
{
	free(m->xy);
	free(m->map);
}

void	clear_cub(t_cub *c)
{
	clear_map(&c->m);
	release_events(c->ev);
	if (c->mlx_win)
		mlx_destroy_window(c->mlx, c->mlx_win);
	clear_gfx(&c->g, c->mlx);
	clear_img(c->fb_swap, c->mlx);
	clear_img(c->fb, c->mlx);
	free(c);
}
