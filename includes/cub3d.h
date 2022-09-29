#ifndef CUB3D_H
# define CUBD3D_H

/************************LIBS**************************/

# include "./libft/libft.h"
# include "./mlx/mlx.h"

/****************DEFINES_KEYBOARD*********************/

# define KB_D 2
# define KB_A 0
# define KB_W 13
# define KB_S 1
# define KB_LEFT 123
# define KB_RIGHT 124
# define ESCAPE_KC 53

typedef struct s_data
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;

	/* Use of unsigned array of size 3 because RGB contains 3 values between 0 and 255*/
	unsigned char	floor_color[3];
	unsigned char	ceil_color[3];
	
	char			**map;
}				t_data;

#endif