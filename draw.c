/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 13:04:20 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/06 17:50:17 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline t_pixel	lerp(t_pixel a, t_pixel b, float t)
{
	t_pixel	res;

	res.bits.a = 0;
	res.bits.r = a.bits.r + t * (b.bits.r - a.bits.r);
	res.bits.g = a.bits.g + t * (b.bits.g - a.bits.g);
	res.bits.b = a.bits.b + t * (b.bits.b - a.bits.b);
	return (res);
}

inline void	draw_px(t_img *img, int x, int y, t_pixel p)
{
	img->pix[y][x] = p.ucol;
}

inline t_pixel	pick_px(t_img *img, int x, int y)
{
	return ((t_pixel)img->pix[y][x]);
}
