/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnguyen- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:37:02 by aberneli          #+#    #+#             */
/*   Updated: 2022/07/12 22:21:46 by tnguyen-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "mlx_input.h"
# include <mlx.h>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <math.h>

// Error messages
# define ERR_NO_MISSING "North Texture is missing.\n"
# define ERR_SO_MISSING "South Texture is missing.\n"
# define ERR_EA_MISSING "East Texture is missing.\n"
# define ERR_WE_MISSING "West Texture is missing.\n"
# define ERR_FLOOR_MISSING "Floor data is missing.\n"
# define ERR_CEIL_MISSING "Ceiling data is missing.\n"
# define ERR_NO_REDEF "North Texture defined multiple times.\n"
# define ERR_SO_REDEF "South Texture defined multiple times.\n"
# define ERR_EA_REDEF "East Texture defined multiple times.\n"
# define ERR_WE_REDEF "West Texture defined multiple times.\n"
# define ERR_FLOOR_REDEF "Floor data defined multiple times.\n"
# define ERR_CEIL_REDEF "Ceiling data defined multiple times.\n"
# define ERR_FLOOR_INVALID "Floor data: incorrect amount of parameters.\n"
# define ERR_CEIL_INVALID "Ceiling data: incorrect amount of parameters.\n"
# define ERR_FLOOR_COLOR "Floor color data is not in range [0 - 255].\n"
# define ERR_CEIL_COLOR "Ceiling color data is not in range [0 - 255].\n"
# define ERR_INVALID_MAPCHAR "Map contains invalid character.\n"
# define ERR_EMPTY_MAP "Map is empty or has no terrain data.\n"
# define ERR_MULTIPLE_SPAWNS "Map has multiple spawn locations.\n"
# define ERR_NO_SPAWN "Missing spawn location.\n"
# define ERR_WRONG_BORDER "Map is not properly bordered.\n"
# define ERR_UNEXPECTED_CHAR "Unexpected character within map data.\n"
# define ERR_UNEXPECTED_EMPTY "Unexpected empty line within map data.\n"

# define ERR_ALLOC "Not enough memory.\n"
# define ERR_MLX_ALLOC "mlx allocation failure.\n"
# define ERR_MLX_FAIL "mlx init failure.\n"
# define ERR_BADFILE "Cannot open map file.\n"
# define ERR_BADTEX "Cannot open texture file.\n"
# define ERR_NO_FILE "Missing map file in argument.\n"
# define ERR_TOO_MANY_ARGS "Too many arguments.\n"
# define ERR_NOT_CUB "Incorrect map file extension.\n"

# define VALID_MAP_STR "NSWE01 "
# define CUB_EXTENSION ".cub"

# define WIN_W 1660
# define WIN_H 900

# define FOG 0x121212

// 7.0 / 60.0 and 3.0 / 60.0, norme wasn't taking it *shrug*
# define MSPD (0.11666)
# define RSPD (0.05)

typedef unsigned char	t_px;

typedef struct s_argb
{
	t_px		b;
	t_px		g;
	t_px		r;
	t_px		a;
}				t_argb;

typedef union u_pixel
{
	int			icol;
	uint32_t	ucol;
	t_argb		bits;
	t_px		raw[4];
}				t_pixel;

typedef struct s_data
{
	char		*map_path;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	char		*tmpf;
	char		*tmpc;
	float		pang;
	t_pixel		f;
	t_pixel		c;
	int			debut;
	int			fin;
	int			largeur;
	int			fd;
	int			px;
	int			py;
	int			pdir;
}				t_data;

typedef struct s_player
{
	float		x;
	float		y;
	float		dirx;
	float		diry;
	float		planex;
	float		planey;
	float		angle;
}				t_player;

typedef struct s_map
{
	int			*map;
	int			**xy;
	int			w;
	int			h;
}				t_map;

typedef struct s_img
{
	void		*img;
	void		*px;
	uint32_t	**pix;
	int			w;
	int			h;
	int			bpp;
	int			stride;
	int			endian;
}				t_img;

typedef struct s_gfx
{
	t_img		*textures[4];
	t_pixel		fcolor;
	t_pixel		ccolor;
}				t_gfx;

typedef struct s_dda
{
	double		rdirx;
	double		rdiry;
	double		sdistx;
	double		sdisty;
	double		ddistx;
	double		ddisty;
	double		camx;
	double		pdist;
	double		fogdist;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineh;
	int			beg;
	int			end;
}				t_dda;

typedef struct s_cub
{
	t_gfx		g;
	t_map		m;
	t_player	p;
	t_img		*fb;
	t_img		*fb_swap;
	t_event		*ev;
	void		*mlx;
	void		*mlx_win;
	int			refresh;
}				t_cub;

// load_textures.c
int		load_xpm(t_data *d, t_cub *c);

// draw.c
t_pixel	lerp(t_pixel a, t_pixel b, float t);
void	draw_px(t_img *img, int x, int y, t_pixel p);
t_pixel	pick_px(t_img *img, int x, int y);

// clear.c
int		clear_data(t_data *d);
void	clear_gfx(t_gfx *f, void *mlx);
void	clear_map(t_map *m);
void	clear_cub(t_cub *c);

// init.c
int		init_cub(t_cub *c, char *path);

// image.c
t_img	*new_img(void *mlx, int w, int h);
t_img	*new_img_xpm(void *mlx, char *path);
void	clear_img(t_img *img, void *mlx);

// move.c
void	strafe_player(t_cub *p);
void	move_player(t_cub *p);
void	orient_player(t_cub *p);

// dda.c
void	dda(t_cub *c);

// dda2.c
void	pick_texel(t_cub *c, t_dda *d, int x);

// display.c
int		quit_hook(void	*p);
int		loop_hook(void *p);

// mapping.c
int		mapping(t_data *d, t_cub *c, char *fichier);

// parsing.c
int		parsing(t_data *d);

// checks
int		check_cardinals(t_data *d, char *line);
int		check_garbage(char *line);
int		check_map_border(t_cub *c);

// functions.c
size_t	ft_strlen(char const *s);
char	*ft_strdup(char const *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memset(void *dst, int v, size_t len);
char	*ft_skipstrdup(char const *s);

// utils.c
int		print_error(char const *error, void *ptr);
int		validate_str(char *s1, char s2);
int		ft_atoi(const char *str);

// split.c
void	*ft_split_free(char **spl);
char	**ft_split(char const *str, char c);

// color.c
int		parse_color(t_data *d, t_gfx *g);

#endif
