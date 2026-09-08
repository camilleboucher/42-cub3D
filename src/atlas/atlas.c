#include "cube3D2.h"

#include "frame_buffer.h"

void free_all_images(t_app *app) {
    unsigned int i;

    i = 0;
    while (i < app->image_atlas.image_amount)
    {
        if (app->image_atlas.images[i])
            free(app->image_atlas.images[i++]);
    }
}

void copy_image_to_region(t_app *app, t_region *region, mlx_image image, t_vec2i size) {
    int x;
    int y;

    x = 0;
    while (x < size.x)
    {
        y = 0;
        while (y < size.y)
        {
            mlx_color color = mlx_get_image_pixel(app->ctx, image, x, y);
            set_pixel(region, x, y, color);
            y++;
        }
        x++;
    }
}

void copy_image_to_region_hflip(t_app *app, t_region *region, mlx_image image, t_vec2i size) {
    int x;
    int y;

    x = 0;
    while (x < size.x)
    {
        y = 0;
        while (y < size.y)
        {
            mlx_color color = mlx_get_image_pixel(app->ctx, image, size.x - x - 1, y);
            set_pixel(region, x, y, color);
            y++;
        }
        x++;
    }
}

t_region *load_image(t_app *app, char *path, bool hflip)
{
    t_region *region;
    mlx_image img;
    t_vec2i size;

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
    if (hflip)
        copy_image_to_region_hflip(app, region, img, size);
    else
        copy_image_to_region(app, region, img, size);
    mlx_destroy_image(app->ctx, img);
    return (region);
}

bool atlas_load_buttons(t_app *app) {
    unsigned int i;

    i = 0;
    app->image_atlas.images[i] = load_image(app, "assets/play_button.png", false);            // 0
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/play_button_hover.png", false);      // 1
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/stone.png", true);                   // 2
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/east.png", true);                    // 3
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/west.png", true);                    // 4
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/north.png", true);                   // 5
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/south.png", true);                   // 6
    if (!app->image_atlas.images[i++])
        return (false);

    app->image_atlas.images[i] = load_image(app, "assets/map/indicator_north.png", false);    // 7
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/map/indicator_south.png", false);    // 8
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/map/indicator_east.png", false);     // 9
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/map/indicator_west.png", false);     // 10
    if (!app->image_atlas.images[i++])
        return (false);
    app->image_atlas.images[i] = load_image(app, "assets/map/frame.png", false);              // 11
    if (!app->image_atlas.images[i++])
        return (false);
    return (true);
}
