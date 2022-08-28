/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:32:27 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/06 14:19:28 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_player(t_data *d, char *line, int i, int j)
{
	if ((line[j] == 'N' || line[j] == 'S' || line[j] == 'E' || line[j] == 'W'))
	{
		if (d->pdir != 0)
			return (print_error(ERR_MULTIPLE_SPAWNS, line));
		d->px = j;
		d->py = i;
		d->pdir = line[j];
	}
	if (line[j] == 'N')
		d->pang = M_PI / 2 * 3;
	else if (line[j] == 'S')
		d->pang = M_PI / 2;
	else if (line[j] == 'E')
		d->pang = 0;
	else if (line[j] == 'W')
		d->pang = M_PI;
	return (0);
}

static int	parse_map(t_cub *c, t_data *d, char *line, int i)
{
	int	j;

	j = 0;
	if (line[j] == '\n')
		return (print_error(ERR_UNEXPECTED_EMPTY, line));
	while (line[j] && line[j] != '\n')
	{
		if (line[j] == ' ' || line[j] == '1')
			c->m.xy[i][j] = 1;
		else if (get_player(d, line, i, j) < 0)
			return (-1);
		else if (validate_str("0NSWE", line[j]) < 0)
		{
			dprintf(2, "%c %d\n", line[j], j);
			return (print_error(ERR_UNEXPECTED_CHAR, line));
		}
		j++;
	}
	while (j < c->m.w)
		c->m.xy[i][j++] = 1;
	free(line);
	return (0);
}

static int	ft_read(t_data *d, t_cub *c, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < d->debut)
	{
		i++;
		free(get_next_line(fd));
	}
	line = get_next_line(fd);
	while (line)
	{
		if (parse_map(c, d, line, i - d->debut) == -1)
			return (-1);
		line = get_next_line(fd);
		i++;
	}
	return (0);
}

static int	remplissage(t_data *d, t_cub *c, char *fichier)
{
	int		fd;

	fd = open(fichier, 0);
	if (fd < 0)
		return (print_error(ERR_BADFILE, NULL));
	if (ft_read(d, c, fd) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	mapping(t_data *d, t_cub *c, char *fichier)
{
	int	i;

	c->m.h = d->fin - d->debut;
	c->m.w = d->largeur;
	c->m.map = malloc(sizeof(int) * c->m.w * c->m.h);
	if (!c->m.map)
		return (print_error(ERR_ALLOC, NULL));
	ft_memset(c->m.map, 0, sizeof(int) * c->m.w * c->m.h);
	c->m.xy = malloc(sizeof(int *) * c->m.h);
	if (!c->m.xy)
		return (print_error(ERR_ALLOC, NULL));
	i = 0;
	while (i < c->m.h)
	{
		c->m.xy[i] = &c->m.map[i * c->m.w];
		i++;
	}
	return (remplissage(d, c, fichier));
}
