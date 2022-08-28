/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:55:34 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/05 14:35:38 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_xpm(t_data *d, t_cub *c)
{
	if (!d->no)
		return (print_error(ERR_NO_MISSING, NULL));
	c->g.textures[0] = new_img_xpm(c->mlx, d->no);
	if (!c->g.textures[0])
		return (-1);
	if (!d->so)
		return (print_error(ERR_SO_MISSING, NULL));
	c->g.textures[1] = new_img_xpm(c->mlx, d->so);
	if (!c->g.textures[1])
		return (-1);
	if (!d->we)
		return (print_error(ERR_WE_MISSING, NULL));
	c->g.textures[2] = new_img_xpm(c->mlx, d->we);
	if (!c->g.textures[2])
		return (-1);
	if (!d->ea)
		return (print_error(ERR_EA_MISSING, NULL));
	c->g.textures[3] = new_img_xpm(c->mlx, d->ea);
	if (!c->g.textures[3])
		return (-1);
	return (0);
}
