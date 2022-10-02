#include "test.h"

t_bool	test_data_struct(void)
{
	t_data			*data;
	DIR 			*d;
    struct dirent 	*dir;
    char 			full_path[1000];
    char			path[18] = "unit-tests/scenes";

    d = opendir(path);
    if (d)
    {
		// THIS LOOP WILL ITERATE OVER ALL THE .cub maps in the scene folder
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_type==DT_REG){
                full_path[0]='\0';
                strcat(full_path,path);
                strcat(full_path,"/");
                strcat(full_path,dir->d_name);

				data = init_data(full_path);
				free_data(data);
            }
        }
        closedir(d);
    }
    return(0);   
}