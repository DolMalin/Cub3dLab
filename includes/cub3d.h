#ifndef CUB3D_H
# define CUB3D_H

/************************LIBS**************************/

# include "../libft/libft.h"
# include "../mlx/mlx.h"

/****************DEFINES_PREFERENCES******************/
# define PRINT_COEF			10
# define ROT_COEF			20
# define STEP_COEF			0.1
# define WIN_WIDTH			1200
# define WIN_HEIGHT			900
# define FOV				600
# define FOV_STEP			0.00175
# define FOV_AMPLITUDE		FOV * FOV_STEP * 0.5
# define FLOAT_LINE			WIN_HEIGHT * 0.5
# define STRIPE				WIN_WIDTH / FOV
# define CUB_SIZE			1
# define SPRITE_SIZE		100

/****************DEFINES_RADIANS******************/

#define TWO_PI 6.28318530718
#define PI_ON_TWO 1.57079632679
#define THREE_PI_ON_TWO 4.71238898038
# define PI 3.14159265359

/****************DEFINES_KEYBOARD*********************/

# define KB_D 2
# define KB_A 0
# define KB_W 13
# define KB_S 1
# define KB_LEFT 123
# define KB_RIGHT 124
# define ESCAPE_KC 53

/****************DEFINES_SCENE*********************/

# define NO 0
# define SO 1
# define EA 2
# define WE 3

# define FLOOR 0
# define CEIL 1

# define R 0
# define G 1
# define B 2

/****************DEFINES_ERRORS*********************/

# define ARGS "wrong arguments."
# define CONFIG_STRUCT "wrong configuration lines or structure of scene."
# define MAP "wrong map."
# define TEXTURES "wrong textures paths or format."
# define RGB_CODES "wrong RGB color codes."
# define MEMALLOC "can't allocate memory."
# define OPENFILE "can't open file."

typedef enum e_bool
{
	false,
	true
}			t_bool;


typedef struct s_ray 
{
	float	x_end;
	float	y_end;
	int		dir;
	float	angle;
	float	len;
	t_bool	coll;
}				t_ray;

typedef struct s_image 
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_texture 
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;

}				t_texture;

typedef struct s_player 
{
	float	x;
	float	y;
	float	pov;
	float	ray_coef_x;
	float	ray_coef_y;
}				t_player;


typedef struct s_precomputed
{
	float			float_line;
	float			fov_amplitude;
	int				stripe;
	int				*map_lines_len;
}				t_precomputed;

typedef struct s_data
{
	char			**textures_path;
	t_texture		**textures;
	unsigned char	**colors;
	int				color_ceil;
	int				color_floor;
	char			**map;
	int				y_max;
	void			*mlx;
	void			*mlx_win;
	t_image			*image;
	t_player		*player;
	t_precomputed	*precomputed;
}				t_data;

/******** TO REMOVE*********/
void print_map(char **map);

/****************GRAPHIC*********************/
int				create_image(t_data *data);
void			print_bigger(t_image *image, float x, float y, int color_code);
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);

t_ray			*get_collision_coord(t_data *data, float pov);

void    		raycasting(t_data *data);
void			draw_line(t_data *data, float end_x, float end_y);
float			get_y_with_x(t_data *data, float x, float pov);
float			get_x_with_y(t_data *data, float y, float pov);
float			get_fixed_ray_end(t_ray *ray, char dir, float pov);
float			get_ray_len(t_data *data, t_ray *ray);
int				rgb_to_hex(unsigned char *rgb);
int				get_wall_dir(t_ray *ray, char dir, float pov);
int				get_pixel_from_sprite_x(t_data *data, float pov);
int				get_pixel_from_sprite_y(t_data *data, float wall_height, int wall_cursor_y);

/****************ACTION*********************/
void			run_game(t_data *data);

int				move_player(t_data *data, int key);
void			get_player_pos(t_data **data);
void			update_player_pov(t_data **data);
char			get_player_token(t_data *data);

void			move_right(t_data **data);
void			move_left(t_data **data);
void			move_down(t_data **data);
void			move_up(t_data **data);
void			rotate_left(t_data **data);
void			rotate_right(t_data **data);

/****************CHECK_INPUT*********************/
t_bool			check_input(int ac, char **av);
t_bool			check_config_structure(char **scene);
t_bool			check_map(char **unparsed_scene);
t_bool			check_player(char **map);
t_bool			check_colors(char **unparsed_scene);
t_bool			check_color_code(char *color);
t_bool			check_textures(char **scene);

/****************PARSING*********************/
t_data			*init_data(char *scene_file);
void			free_data(t_data *data);
char			*get_line_from_key(char	**parsed_scene, char *key);
unsigned char	**get_colors(char **parsed_scene);
char			**get_textures_paths(char **parsed_scene);
char			**get_map(char	**parsed_scene);
char			**parse_scene_file(char *scene_file);
char			*trim(char *line, char *charset);
char			**trim_config_line(char **parsed_scene);
t_player		*init_player(t_data *data);

/****************UTILS*********************/
int				lines_count(char *file);
void			free_array(void	**array);
size_t			array_len(void **array);
t_bool			is_config_line(char	*line);
void			free_unterminated_array(void **array, size_t n);
t_bool			is_empty_line(char *line);
t_bool			ft_strisdigit(char *str);
t_bool			is_in_charset(char c, char *charset);
t_bool			is_near_charset(char **unparsed_scene, size_t i, size_t j, char *charset);
void			print_config(t_data *data);

/****************ERRORS*********************/
void	error(char *error_msg);

t_bool	is_near_void(char **unparsed_scene, size_t i, size_t j);
#endif