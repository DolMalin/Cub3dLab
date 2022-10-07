#include "../../includes/cub3d.h"

// static t_bool   check_color_code(unsigned char *color, const char *color_id)
// {

//     if (!((color[R] >= 0 && color[R] <= 255) 
//         && (color[G] >= 0 && color[G] <= 255) 
//             && (color[B] >= 0 && color[B] <= 255)))
//     {
//             printf("Wrong RGB color code for %s\n", color_id);
//             return (false);
//     }
//     return (true); // think about the case when there is nothing between 2 "," example : "200,,300"
// }

// static t_bool   check_color_code(char *color_line, const char *color_id)
// {
//     unsigned char   *color;
//     char            **splited_line;

//     splited_line = ft_split(color_line, ',');
//     if (!splited_line)
//         return (false);
//     color = malloc(sizeof(unsigned char) * 3);
//     if (!color)
//         return (false);
//     color[R] = (unsigned char)ft_atoi(&splited_line[0][2]);
//     color[G] = (unsigned char)ft_atoi(splited_line[1]);
//     color[B] = (unsigned char)ft_atoi(splited_line[2]); // make a function to get the color and seperate from check_color
//     // the condition below condition condition simplified
//     if (!((color[R] >= 0 && color[R] <= 255) 
//         && (color[G] >= 0 && color[R] <= 255) 
//             && (color[B] >= 0 && color[R] <= 255)))
//     {
//             free(color);
//             free(splited_line);
//             printf("Wrong RGB color code for %s definition\n", color_id);
//             return (false);
//     }
//     free(color);
//     free(splited_line);
//     return (true); // think about the case when there is nothing between 2 "," example : "200,,300"
// }

// /*
// static t_bool   check_color_codes(char **unparsed_scene)
// {
// 	unsigned char **colors;

// 	colors = get_colors(unparsed_scene);
// 	printf("%d %d %d\n", colors[FLOOR][R], colors[FLOOR][G], colors[FLOOR][B]);
// 	printf("%d %d %d\n", colors[CEIL][R], colors[CEIL][G], colors[CEIL][B]);
// 	if (!check_color_code(colors[FLOOR], "floor"))
// 	{
// 		free_unterminated_array((void **)colors, 2);
// 		return (false);
// 	}
// 	if (!check_color_code(colors[CEIL], "ceiling"))
// 	{
// 		free_unterminated_array((void **)colors, 2);
// 		return (false);
// 	}
// 	free_unterminated_array((void **)colors, 2);
//     return (true);
// }*/

// static t_bool   check_color_codes(char **unparsed_scene)
// {
//     if (!check_color_code(get_line_from_key(unparsed_scene, "F"), "Floor")) // find a way to verify if the line is missing to have an error message "no floor color code indicated"
//         return (false);
//     if (!check_color_code(get_line_from_key(unparsed_scene, "C"), "Ceiling"))
//         return (false);
//     return (true);
// }

// static t_bool	check_color_lines(char **unparsed_scene)
// {
// 	if (!get_line_from_key(unparsed_scene, "F"))
// 	{
// 		printf("No floor colour written in scene file\n");
// 		return (false); 
// 	}
// 	if (!get_line_from_key(unparsed_scene, "C"))
// 	{
// 		printf("No ceiling colour written in scene file\n");
// 		return (false);
// 	}
// 	return (true);
// }

static char	**get_colors_to_check(char **unparsed_scene)
{
	char	**colors;

	colors = malloc(sizeof(char *) * 4);
	if (!colors)
		return (NULL);
	colors[FLOOR] = get_line_from_key(unparsed_scene, "F");
	colors[CEIL] = get_line_from_key(unparsed_scene, "C");
	colors[2] = 0;
	return (colors);
}

static t_bool	check_color_code(char *color)
{
	char 	**split_color;
	int		i;

	split_color = ft_split(color, ',');
	i = 0;
	while (split_color[i])
	{
		//printf("color %d : %d\n", i, ft_atoi(split_color[i]));
		if (!(ft_atoi(split_color[i]) >= 0 && (ft_atoi(split_color[i]) <= 255)))
		{
			printf("Error in color code. Color code must be between 0 and 255.\n");
			free_array((void **)split_color);
			return (false);
		}
		i++;
	}
	if (i != 3)
	{
		printf("Not the right structure for color code. Must be composed by 3 colors : RGB.\n");
		return (false);
	}
	free_array((void **)split_color);
	return (true);
}

static int coma_count(char *color)
{
	int	i;
	int	coma_count;

	i = 0;
	coma_count = 0;
	while (color[i])
	{
		if (color[i] == ',')
			coma_count++;
		i++;
	}
	return (coma_count);
}

static t_bool check_comas(char **colors)
{
	if (coma_count(colors[CEIL]) != 2)
	{	
		printf("Check comas in the color code, must be one to seperate each colour\n");
		return (false);
	}
	if (coma_count(colors[FLOOR]) != 2)
	{	
		printf("Check comas in the color code, must be one to seperate each colour\n");
		return (false);
	}
	return (true);
}

t_bool	check_colors(char **unparsed_scene)
{
	char **colors;

	colors = get_colors_to_check(unparsed_scene);
	if (!check_comas(colors))
		return (false);
	if (!check_color_code(colors[FLOOR]))
		return (false);
	if (!check_color_code(colors[CEIL]))
		return (false);
	// printf("\tcolor floor%s\n",colors[0]);
	// printf("\tcolor ceiling%s\n",colors[1]);
	free_array((void **)colors);
	return (true);
}