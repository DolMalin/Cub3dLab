#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	print_bigger(t_image *image, int x, int y, int color_code)
{
	int i = 0;
	int j = 0;

	i = 0;
	while (i < PRINT_COEF)
	{
		j = 0;
		while (j < PRINT_COEF)
		{
			my_mlx_pixel_put(image, (x * PRINT_COEF) + i + 20, (y * PRINT_COEF) + j + 20, color_code);
			j++;
		}
		i++;
	}
}