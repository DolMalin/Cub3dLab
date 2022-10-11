#ifndef CUB3D_H
# define CUB3D_H

/************************LIBS**************************/

# include "../libft/libft.h"
// # include "./mlx/mlx.h"

/****************DEFINES_KEYBOARD*********************/

# define KB_D 2
# define KB_A 0
# define KB_W 13
# define KB_S 1
# define KB_LEFT 123
# define KB_RIGHT 124
# define ESCAPE_KC 53

# define NO 0
# define SO 1
# define EA 2
# define WE 3

# define FLOOR 0
# define CEIL 1

# define R 0
# define G 1
# define B 2

typedef struct s_data
{
	char			**textures_path;
	/* Use of unsigned array of size 3 because RGB contains 3 values between 0 and 255*/
	unsigned char	**colors;
	char			**map;
}				t_data;

typedef enum e_bool
{
	false,
	true
}			t_bool;

/******** TO REMOVE*********/
void print_map(char **map);

/****************CHECK_INPUT*********************/
t_bool			check_input(int ac, char **av);
t_bool			check_map(char **unparsed_scene);
t_bool			check_colors(char **unparsed_scene);
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

/****************UTILS*********************/
int		lines_count(char *file);
void	free_array(void	**array);
size_t	array_len(void **array);
t_bool	is_config_line(char	*line);
void	free_unterminated_array(void **array, size_t n);
t_bool	is_empty_space(char c);
t_bool	is_empty_line(char *line);
t_bool	is_near_void(char **unparsed_scene, size_t i, size_t j);
t_bool	ft_strisdigit(char *str);
t_bool is_in_charset(char c, char *charset);

#endif