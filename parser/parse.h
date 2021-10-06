#ifndef PARSE_H
# define PARSE_H

# define LEN_R 1	/* Rename to OFFSET_R */
# define LEN_NO 2
# define LEN_SO 2
# define LEN_WE 2
# define LEN_EA 2
# define LEN_S 1
# define LEN_F 1
# define LEN_C 1

# define RGB_DATA_COUNT 3
# define RESOLUTION_DATA_COUNT 2
# define MAX_KOMMAS 2

# define STACK_MAX 10000

# define UNIT 1

typedef struct s_parse
{
    int     		win_width;
    int     		win_height;
    char    		*north_text;
    char    		*south_text;
    char    		*west_text;
    char    		*east_text;
    int             floor_colour[RGB_DATA_COUNT];
    int             ceiling_colour[RGB_DATA_COUNT];
	char			**map;
}			t_parse;

typedef struct s_recursion_management
{
	unsigned int	i;
	unsigned int	total_recursions;
	char			max_stack_reached;
	int				save_x;
	int				save_y;
	char			error;

}	t_recursion_management;

/* parse_main.c */
int     parse_main(t_parse *parse, char **argv);

/* init.c */
void	parse_init(t_parse *parse);
void	recursion_management_init(t_recursion_management *rec_man);

/* parse_data.c */
int  	parse_data(int fd, t_parse *parse);
int 	decision(int fd, t_parse *parse, char *line);

/* parse_resolution.c */
int   	parse_resolution(int *win_width, int *win_height, char *line);

/* parse_textures.c */
int 	parse_textures(t_parse *parse, char *line);
int    	fill_texture(char **texture, char *line, char *text_id);

/* parse_colour.c */
int     parse_colour(int *colour_array, char *line);
int		fill_colour(int *colour_array, char *line);

/* parse_map.c */
int    	parse_map(int fd, t_parse *parse, char *line);
char  	**create_map(t_parse *parse, char *line, int rows);
int    	old_to_new_map(t_parse *parse, char **new_map, int rows);

/* checks.c */
int     check_resolution(char *line);
int 	check_map(char **map);
int		check_data_completeness(t_parse *parse);

/* print.c */
void    print_parse(t_parse *parse);
void    print_map(char **map);

/* error.c */
int		error_colour(void);
//void    *error_malloc(void);

/* utils.c */
int     skip_chr(char *str, int c);
void    find_player_location(int *x, int *y, char **map);
char 	**copy_map(char **map);

/* flood_fill.c */
int 	flood_fill(int x, int y, char **map, t_recursion_management *rec_man);

/* free_data.c */
void    free_parse(t_parse *parse);
void	free_textures(t_parse *parse);
void	free_map(char **map);

#endif