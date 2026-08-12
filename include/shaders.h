#ifndef SHADERS_H
#define SHADERS_H

void blur_pixel(t_app *app, t_vec2i coords, int distance, int steps);
void apply_blur(t_app *app, int distance, int quality);

#endif