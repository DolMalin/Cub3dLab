//#include "../../includes/cub3d.h"

// static t_bool   check_texture(char *texture_line, const char *texture_id)
// {
//     if (!texture_line)
//     {
//         printf("No texture found for %s walls\n", texture_id);
//         return (false);
//     }
//     if (open(texture_line, O_RDONLY) < 0)
//     {
//         printf("Can't access the %s texture file\n", texture_id);
//         return (false);
//     }
//     return (true);
// }

// static t_bool   check_textures(char **unparsed_scene)
// {
//     if (!check_texture(get_line_from_key(unparsed_scene, "NO"), "NO")) // verify if get_line_from_key gives path or line cf get path seems like it does
//         return (false);
//     if (!check_texture(get_line_from_key(unparsed_scene, "SO"), "SO")) // verify how to free linke from key
//         return (false);
//     if (!check_texture(get_line_from_key(unparsed_scene, "ES"), "ES"))
//         return (false);
//     if (!check_texture(get_line_from_key(unparsed_scene, "WE"), "WE"))
//         return (false);
//     return (true);
// }