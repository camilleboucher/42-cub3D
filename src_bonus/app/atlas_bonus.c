/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 18:36:50 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/11 17:57:15 by cboucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	free_all_images(t_app *app)
{
	unsigned int	i;

	i = 0;
	while (i < app->image_atlas.image_amount)
	{
		if (app->image_atlas.images[i])
			free(app->image_atlas.images[i]);
		i++;
	}
}

void	copy_image_to_region_hflip(t_app *app, t_region *region,
	mlx_image image, t_vec2i size)
{
	int			x;
	int			y;
	mlx_color	color;

	x = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			color = mlx_get_image_pixel(app->ctx, image, size.x - x - 1, y);
			set_pixel(region, x, y, color);
			y++;
		}
		x++;
	}
}

void	copy_image_to_region(t_app *app, t_region *region, mlx_image image,
		t_vec2i size)
{
	int			x;
	int			y;
	mlx_color	color;

	x = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			color = mlx_get_image_pixel(app->ctx, image, x, y);
			set_pixel(region, x, y, color);
			y++;
		}
		x++;
	}
}

t_region	*load_image(t_app *app, const char *path, bool hflip, mlx_image img)
{
	t_region	*region;
	t_vec2i		size;

	img = mlx_new_image_from_file(app->ctx, path, &size.x, &size.y);
	if (img == MLX_NULL_HANDLE)
	{
		free_all_images(app);
		return (NULL);
	}
	region = malloc(sizeof(t_region) + size.x * size.y * sizeof(mlx_color));
	if (!region)
	{
		free_all_images(app);
		if (img != MLX_NULL_HANDLE)
			mlx_destroy_image(app->ctx, img);
		return (NULL);
	}
	region->width = size.x;
	region->height = size.y;
	if (hflip)
		copy_image_to_region_hflip(app, region, img, size);
	else
		copy_image_to_region(app, region, img, size);
	mlx_destroy_image(app->ctx, img);
	return (region);
}

bool	atlas_load_buttons(t_app *app)
{
	unsigned int		i;
	mlx_image			img;
	const char *const	files[] = {TEX_0, TEX_1, TEX_2,
		app->map.path_textures[1], app->map.path_textures[0],
		app->map.path_textures[3], app->map.path_textures[2],
		TEX_7, TEX_8, TEX_9, TEX_10, TEX_11, TEX_12, TEX_13, TEX_14,
		TEX_15, TEX_16, TEX_17, TEX_18, TEX_19, TEX_20, TEX_21, TEX_22,
		TEX_23, TEX_24, TEX_25, TEX_26, TEX_27, TEX_28, TEX_29, TEX_30,
		TEX_31, TEX_32, TEX_33, TEX_34, TEX_35, TEX_36, TEX_37, TEX_38,
		TEX_39, TEX_40};

	app->image_atlas.image_amount = 0;
	i = 0;
	while (i < sizeof(files) / sizeof(char *))
	{
		img = NULL;
		app->image_atlas.images[app->image_atlas.image_amount] = load_image(app,
				files[i], i == 4 || i == 5, img);
		if (!app->image_atlas.images[app->image_atlas.image_amount++])
			return (false);
		i++;
	}
	app->image_atlas.animated_sprite[0] = animated_sprite_from_region(
			app->image_atlas.images[22], 54, 0.03, true);
	return (true);
}
