/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 13:16:41 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/05 17:15:38 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	spl_len(char **spl)
{
	int	i;

	i = 0;
	while (spl[i])
		i++;
	return (i);
}

static int	parse_color_step(char **spl, t_px *raw)
{
	int	i;
	int	test;

	i = 0;
	while (i < 3)
	{
		test = ft_atoi(spl[i]);
		if (test < 0)
			return (-1);
		raw[2 - i] = test;
		i++;
	}
	return (0);
}

static int	parse_color_floor(t_data *d, t_gfx *g)
{
	char	**tmp;
	int		len;

	tmp = ft_split(d->tmpf, ',');
	if (!tmp)
		return (print_error(ERR_ALLOC, NULL));
	len = spl_len(tmp);
	if (len != 3)
	{
		ft_split_free(tmp);
		return (print_error(ERR_FLOOR_INVALID, NULL));
	}
	if (parse_color_step(tmp, g->fcolor.raw) < 0)
	{
		ft_split_free(tmp);
		return (print_error(ERR_FLOOR_COLOR, NULL));
	}
	ft_split_free(tmp);
	return (0);
}

static int	parse_color_ceil(t_data *d, t_gfx *g)
{
	char	**tmp;
	int		len;

	tmp = ft_split(d->tmpc, ',');
	if (!tmp)
		return (print_error(ERR_ALLOC, NULL));
	len = spl_len(tmp);
	if (len != 3)
	{
		ft_split_free(tmp);
		return (print_error(ERR_CEIL_INVALID, NULL));
	}
	if (parse_color_step(tmp, g->ccolor.raw) < 0)
	{
		ft_split_free(tmp);
		return (print_error(ERR_CEIL_COLOR, NULL));
	}
	ft_split_free(tmp);
	return (0);
}

int	parse_color(t_data *d, t_gfx *g)
{
	if (parse_color_ceil(d, g) < 0)
		return (-1);
	if (parse_color_floor(d, g) < 0)
		return (-1);
	return (0);
}
