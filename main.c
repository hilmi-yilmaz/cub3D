#include "cub3d.h"
#include "libft/libft.h"

#include <fcntl.h> // for open
#include <stdio.h> // for printf
#include <unistd.h> // for read, write, close
#include <stdlib.h> //for malloc, free

int main(int argc, char **argv)
{
    t_info  info;

    parse_data(&info, argv);
    return (0);
}

void    parse_data(t_info *info, char **argv)
{
    int     fd;
    int     close_return;
    int     res;
    char    *line;

    fd = open(*(argv + 1), O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening %s\n", *(argv + 1));
        exit(1);
    }
    
    res = 1;
    line = NULL;
    while (res > 0)
    {
        res = get_next_line(fd, &line);
        if (*line == 'R')
            parse_resolution(info, line + 1);
        else if (*line == 'N')
            parse_texture(info->north_text, line);
        free(line);
        line = NULL;
    }
    print_info(info);
    close_return = close(fd);
    if (close_return == -1)
    {
        printf("Error closing %s\n", *(argv + 1));
        exit (1);
    }
}

void    parse_resolution(t_info *info, char *line)
{
    int i;

    i = skip_spaces(line);
    info->win_width = ft_atoi(line + i);
    i += ft_nblen(info->win_width, 10);
    info->win_height = ft_atoi(line + i);
}

int parse_texture(char *texture, char *line)
{
    int i;

    i = skip_spaces(line);
    texture = ft_strdup(line + i);
    if (texture == NULL)
        return (-1);
    return (0);
}

void    print_info(t_info *info)
{
    printf("win_width = |%d|\n", info->win_width);
    printf("win_height = |%d|\n", info->win_height);
}

int skip_spaces(char *str)
{
    int i;

    i = 0;
    while (*(str + i) == ' ')
        i++;
    return (i);
}

void    free_info(t_info *info)
{
    free(info->north_text);
}