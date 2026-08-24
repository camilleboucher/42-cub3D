#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec2i
{
	int		x;
	int		y;
}			t_vec2i;

typedef struct s_vec2f
{
	double	x;
	double	y;
}			t_vec2f;

t_vec2f		vec2f_add(t_vec2f a, t_vec2f b);

t_vec2f		vec2f_comp_mul(t_vec2f a, t_vec2f b);

t_vec2f		vec2f_mul(t_vec2f a, double b);

t_vec2f		vec2f_div(t_vec2f a, double b);

double		vec2f_lenght(t_vec2f a);

double		vec2f_dist(t_vec2f a, t_vec2f b);

#endif