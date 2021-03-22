#include <stdlib.h>
#include <stdio.h>

void    free_map(int **map, int rows);
void    print_map(int **map, int rows, int columns);

int main(void)
{
    int **map;
    int columns;
    int rows;

    columns = 5;
    rows = 2;

    /* Create the array and set NULL at the end */
    map = (int **)malloc(sizeof(int *) * (rows));

    int i = 0;
    int j = 0;
    while (i < rows)
    {
        *(map + i) = (int *)malloc(sizeof(int) * columns);
        while (j < columns)
        {
            *(*(map + i) + j) = i + j;
            j++;
        }
        j = 0;
        i++;
    }
    print_map(map, rows, columns);
    free_map(map, rows);
    return (0);
}

void    print_map(int **map, int rows, int columns)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (i < rows)
    {
        while (j < columns)
        {
            printf("%d ", *(*(map + i) + j));
            j++;
        }
        printf("\n");
        j = 0;
        i++;
    }
}

void    free_map(int **map, int rows)
{
    int i;
    
    i = 0;
    while (i < rows)
    {
        free(*(map + i));
        i++;
    }
    free(map);
}