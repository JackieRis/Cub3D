/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:48:18 by tnguyen-          #+#    #+#             */
/*   Updated: 2022/04/26 13:55:18 by aberneli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *dst, int v, size_t len)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)dst;
	i = 0;
	while (i < len)
	{
		p[i] = v;
		i++;
	}
	return (dst);
}

char	*ft_skipstrdup(char const *s)
{
	size_t	len;
	size_t	offset;
	size_t	i;
	char	*res;

	offset = 0;
	while (s[offset] != ' ')
			offset++;
	while (s[offset] == ' ')
			offset++;
	len = ft_strlen(&s[offset]);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[i + offset] != '\n')
	{
		res[i] = s[i + offset];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(char const *s)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
