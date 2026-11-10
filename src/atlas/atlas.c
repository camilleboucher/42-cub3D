/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atlas.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42angouleme.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 18:36:50 by yben-dje          #+#    #+#             */
/*   Updated: 2026/11/09 19:28:45 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

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

t_region	*load_image(t_app *app, const char *path)
{
	t_region	*region;
	mlx_image	img;
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
		mlx_destroy_image(app->ctx, img);
		return (NULL);
	}
	region->width = size.x;
	region->height = size.y;
	copy_image_to_region(app, region, img, size);
	mlx_destroy_image(app->ctx, img);
	return (region);
}

bool	atlas_load_buttons(t_app *app)
{
	unsigned int		i;
	const char *const	files[] = {"assets/play_button.png",
		"assets/play_button_hover.png", "assets/stone.png",
		app->map.path_textures[1], app->map.path_textures[0],
		app->map.path_textures[3], app->map.path_textures[2], "assets/one.png",
		"assets/two.png", "assets/three.png", "assets/four.png",
		"assets/one_hover.png", "assets/two_hover.png",
		"assets/three_hover.png", "assets/four_hover.png",
		"assets/how_many_players_sign.png", "assets/controler.png",
		"assets/keyboard_mouse.png", "assets/keyboard.png",
		"assets/input_slot.png", "assets/ok.png", "assets/ok_hover.png",
		"assets/maomao.png", "assets/door_closed.png",
		"assets/door_almost_closed.png", "assets/door_almost_opened.png",
		"assets/door_opened.png"};

	app->image_atlas.image_amount = 0;
	i = 0;
	while (i < sizeof(files) / sizeof(char *))
	{
		app->image_atlas.images[app->image_atlas.image_amount] = load_image(app,
				files[i++]);
		if (!app->image_atlas.images[app->image_atlas.image_amount++])
			return (false);
	}
	app->image_atlas.animated_sprite[0] = animated_sprite_from_region(
			app->image_atlas.images[22], 54, 0.03, true);
	return (true);
}
