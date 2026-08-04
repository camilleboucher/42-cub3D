typedef struct s_vec2i {
    int x;
    int y;
} t_vec2i;

typedef struct s_vec2f {
    float x;
    float y;
} t_vec2f;

t_vec2f vec2f_add(t_vec2f a, t_vec2f b);

t_vec2f vec2f_comp_mul(t_vec2f a, t_vec2f b);

t_vec2f vec2f_mul(t_vec2f a, float b);

t_vec2f vec2f_div(t_vec2f a, float b);

float vec2f_lenght(t_vec2f a);

float vec2f_dist(t_vec2f a, t_vec2f b);