#include "cube3D2.h"

void draw_rect(t_app *app, t_vec2i pos, t_vec2i size, mlx_color color) {
    unsigned int x;
    unsigned int y;

    x = 0;
    while (x < size.x) {
        y = 0;
        while (y < size.y)
        {
            set_pixel(app->frame_buffer.buffer, x, y, color);
            y++;
        }
        x++;
    }
}


mlx_color	blend_colors(mlx_color a, mlx_color b)
{
	mlx_color	merged;

	if (a.a + b.a > 0xFF)
	{
		b.a = 0xFF - a.a;
	}
	merged.a = a.a + b.a;
	merged.r = (a.r * a.a) / 0xFF + (b.r * b.a) / 0xFF;
	merged.g = (a.g * a.a) / 0xFF + (b.g * b.a) / 0xFF;
	merged.b = (a.b * a.a) / 0xFF + (b.b * b.a) / 0xFF;
	return (merged);
}

void draw_image_strech(t_app *app, t_vec2i pos, t_vec2i size, t_region *image) {
    unsigned int x;
    unsigned int y;
    mlx_color color;

    x = 0;
    while (x < size.x) {
        y = 0;
        while (y < size.y)
        {
            color = blend_colors(get_pixel(app->frame_buffer.buffer, x + pos.x, y + pos.y), get_pixel(image, image->width * x / size.x, image->height * y / size.y));
            set_pixel(app->frame_buffer.buffer, x, y, color);
            y++;
        }
        x++;
    }
}

void tex_button_draw(t_app *app, t_tex_button button) {
    draw_image_strech(app, button.pos, button.size, button.image);
}

bool tex_button_update(t_app *app, t_tex_button button) {
    tex_button_draw(app, button);
    return (false);
}
