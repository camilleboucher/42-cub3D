#include "constants.h"
#include "cube3D2.h"
#include "frame_buffer.h"
#include "mlx_extended.h"
#include "mlx_profile.h"

static bool allocate_buffers(t_app *app)
{
    free(app->frame_buffer.buffer);
    free(app->frame_buffer.shader_buffer);
    free(app->frame_buffer.minimap_frame_buffer);
    free(app->frame_buffer.minimap_overlay_frame_buffer);
    if (app->frame_buffer.frame_buffer_image)
        mlx_destroy_image(app->ctx, app->frame_buffer.frame_buffer_image);
    if (app->frame_buffer.minimap_frame_buffer_image)
        mlx_destroy_image(app->ctx, app->frame_buffer.minimap_frame_buffer_image);
    app->frame_buffer.buffer = NULL;
    app->frame_buffer.shader_buffer = NULL;
    app->frame_buffer.frame_buffer_image = MLX_NULL_HANDLE;
    app->frame_buffer.minimap_frame_buffer = NULL;
    app->frame_buffer.minimap_overlay_frame_buffer = NULL;
    app->frame_buffer.minimap_frame_buffer_image = MLX_NULL_HANDLE;
    app->frame_buffer.minimap_overlay_frame_buffer_image = MLX_NULL_HANDLE;
    app->frame_buffer.buffer = malloc(sizeof(t_region) + sizeof(mlx_color) * (app->frame_buffer.width * app->frame_buffer.height));
    if (!app->frame_buffer.buffer)
        return (false);
    app->frame_buffer.shader_buffer = malloc(sizeof(t_region) + sizeof(mlx_color) * (app->frame_buffer.width * app->frame_buffer.height));
    if (!app->frame_buffer.shader_buffer)
        return (false);
    app->frame_buffer.frame_buffer_image = mlx_new_image(app->ctx, app->frame_buffer.height, app->frame_buffer.width);
    if (app->frame_buffer.frame_buffer_image == MLX_NULL_HANDLE)
        return (false);
    app->frame_buffer.minimap_frame_buffer = malloc(sizeof(t_region) + sizeof(mlx_color) * (app->minimap.size.x * app->minimap.size.y));
    if (!app->frame_buffer.minimap_frame_buffer)
        return (false);
    app->frame_buffer.minimap_overlay_frame_buffer = malloc(sizeof(t_region) + sizeof(mlx_color) * (app->minimap.size.x * app->minimap.size.y));
    if (!app->frame_buffer.minimap_overlay_frame_buffer)
        return (false);
    app->frame_buffer.minimap_frame_buffer_image = mlx_new_image(app->ctx, app->minimap.size.y, app->minimap.size.x);
    if (app->frame_buffer.minimap_frame_buffer_image == MLX_NULL_HANDLE)
        return (false);
    app->frame_buffer.minimap_overlay_frame_buffer_image = mlx_new_image(app->ctx, app->minimap.size.y, app->minimap.size.x);
    if (app->frame_buffer.minimap_overlay_frame_buffer_image == MLX_NULL_HANDLE)
        return (false);

    return (true);
}


bool reallocate_frame_buffer(t_app *app)
{
    if (!allocate_buffers(app))
        return (false);
    app->frame_buffer.buffer->width = app->frame_buffer.width;
    app->frame_buffer.buffer->height = app->frame_buffer.height;
    app->frame_buffer.shader_buffer->width = app->frame_buffer.width;
    app->frame_buffer.shader_buffer->height = app->frame_buffer.height;
    app->frame_buffer.minimap_frame_buffer->width = app->minimap.size.x;
    app->frame_buffer.minimap_frame_buffer->height = app->minimap.size.y;
    app->frame_buffer.minimap_overlay_frame_buffer->width = app->minimap.size.x;
    app->frame_buffer.minimap_overlay_frame_buffer->height = app->minimap.size.y;

    return (true);
}

bool resize_frame_buffer(t_app *app, unsigned int width, unsigned height)
{
    app->frame_buffer.width = width;
    app->frame_buffer.height = height;
    app->minimap.size = (t_vec2i){height / 4, height / 4};
    app->minimap.pos = (t_vec2i){height / 4, height / 4};
    if (!reallocate_frame_buffer(app))
        return (false);
    clear_frame_buffer(app, (mlx_color){.rgba = 0x000000FF});
    clear_region(app->frame_buffer.minimap_frame_buffer, (mlx_color){.rgba = 0x00000000});
    return (true);
}

void push_frame_buffer_to_screen(t_app *app)
{
    static int a = 0;

    a++;
    mlx_clear_window(app->ctx, app->window, (mlx_color){.rgba = 0x000000FF});
    mlx_set_image_region(app->ctx, app->frame_buffer.frame_buffer_image, 0, 0, 
        app->frame_buffer.buffer->height, app->frame_buffer.buffer->width, 
        app->frame_buffer.buffer->buffer);
    mlx_put_transformed_image_to_window(app->ctx, app->window, 
        app->frame_buffer.frame_buffer_image, 
        ((float)app->frame_buffer.width + (float)app->frame_buffer.height) / 2.f, 
        ((float)app->frame_buffer.height - (float)app->frame_buffer.width) / 2.f, -1, 1, 90);

    if (app->minimap.showed)
    {
        mlx_set_image_region(app->ctx, app->frame_buffer.minimap_frame_buffer_image, 0, 0, 
            app->frame_buffer.minimap_frame_buffer->height, app->frame_buffer.minimap_frame_buffer->width, 
            app->frame_buffer.minimap_frame_buffer->buffer);
        mlx_put_transformed_image_to_window(app->ctx, app->window, app->frame_buffer.minimap_frame_buffer_image, app->minimap.pos.x, app->minimap.pos.y - app->minimap.size.y, -1, 1, app->player.angle * 180 / M_PI + 180);
        
        mlx_set_image_region(app->ctx, app->frame_buffer.minimap_overlay_frame_buffer_image, 0, 0, 
            app->frame_buffer.minimap_frame_buffer->height, app->frame_buffer.minimap_frame_buffer->width, 
            app->frame_buffer.minimap_overlay_frame_buffer->buffer);
        mlx_put_transformed_image_to_window(app->ctx, app->window, app->frame_buffer.minimap_overlay_frame_buffer_image, app->minimap.pos.x, app->minimap.pos.y - app->minimap.size.y, -1, 1, 90);
    }
}
