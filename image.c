/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aberneli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:16:22 by aberneli          #+#    #+#             */
/*   Updated: 2022/05/06 11:07:10 by aberneli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	img_ext(t_img *img)
{
	int	i;

	img->px = mlx_get_data_addr(img->img, &img->bpp, &img->stride, \
		&img->endian);
	img->bpp /= 8;
	img->pix = malloc(sizeof(uint32_t *) * img->h);
	if (!img->pix)
		return (print_error(ERR_MLX_ALLOC, img));
	i = 0;
	while (i < img->h)
	{
		img->pix[i] = (uint32_t *)(img->px + i * img->stride);
		i++;
	}
	return (0);
}

t_img	*new_img(void *mlx, int w, int h)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
	{
		print_error(ERR_ALLOC, NULL);
		return (NULL);
	}
	ft_memset(img, 0, sizeof(t_img));
	img->w = w;
	img->h = h;
	img->img = mlx_new_image(mlx, w, h);
	if (!img->img)
	{
		print_error(ERR_MLX_ALLOC, img);
		return (NULL);
	}
	if (img_ext(img) < 0)
	{
		clear_img(img, mlx);
		return (NULL);
	}
	return (img);
}

t_img	*new_img_xpm(void *mlx, char *path)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
	{
		print_error(ERR_ALLOC, NULL);
		return (NULL);
	}
	ft_memset(img, 0, sizeof(t_img));
	img->img = mlx_xpm_file_to_image(mlx, path, &img->w, &img->h);
	if (!img->img)
	{
		print_error(ERR_BADTEX, img);
		return (NULL);
	}
	if (img_ext(img) < 0)
	{
		clear_img(img, mlx);
		return (NULL);
	}
	return (img);
}

void	clear_img(t_img *img, void *mlx)
{
	if (!img)
		return ;
	if (img->img)
		mlx_destroy_image(mlx, img->img);
	free(img->pix);
	free(img);
}
