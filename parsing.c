/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:37:10 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/05/06 14:53:32 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	seriesdeif(t_data *d, char *line)
{
	int	res;

	res = check_cardinals(d, line);
	if (res != 0)
		return (res);
	if (check_garbage(line) < 0)
		return (-1);
	return (0);
}

static int	mapfinder(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '1' || line[i] == '0')
			return (1);
		else
			return (-1);
	}
	return (-1);
}

static int	clacarte(t_data *d, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (validate_str(VALID_MAP_STR, line[i]) == -1)
			return (print_error(ERR_INVALID_MAPCHAR, line));
		i++;
	}
	if (i > d->largeur)
		d->largeur = i;
	return (1);
}

int	parsing(t_data *d)
{
	char	*line;

	line = get_next_line(d->fd);
	d->debut = -1;
	while (line != NULL)
	{
		if (d->debut == -1 && seriesdeif(d, line) == -1)
			return (-1);
		if (d->debut == -1 && mapfinder(line) == 1)
			d->debut = d->fin;
		if (d->debut != -1 && clacarte(d, line) == -1)
			return (-1);
		free(line);
		line = get_next_line(d->fd);
		d->fin++;
	}
	if (!d->no || !d->so || !d->we || !d->ea || !d->tmpf || !d->tmpc)
		return (print_error("Missing Texture or Floor/Ceiling data.\n", NULL));
	return (1);
}
