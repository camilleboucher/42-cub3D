#ifndef SHADERS_H
#define SHADERS_H

void blur_pixel(struct s_app *app, t_vec2i coords, int distance, int steps);
void apply_blur(struct s_app *app, int distance, int quality);

#endif