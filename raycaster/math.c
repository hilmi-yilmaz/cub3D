/* Standard library header files */
#include <math.h>

/* User defined header files */
#include "../cub3d.h"

double	calculate_ray_len(t_player *player, double x, double y)
{
	return(sqrt(pow(fabs(player->x - x), 2) + pow(fabs(player->y - y), 2)));
}

double	calculate_ray_len_1(t_player *player, double x, double angle)
{
	return (fabs((player->x - x) / cos(angle)));
}

void    bounds_angle(double *angle)
{
    if (*angle > 2 * PI)
        *angle -= 2 * PI;
    if (*angle < -2 * PI)
        *angle += 2 * PI;
}

int unit_circle_upper_lower(double angle)
{
    if ((angle >= 0 && angle < PI) || (angle <= -PI && angle > -2 * PI))
        return (0);
    return (1);
}

int unit_circle_left_right(double angle)
{
    /* Substract half PI from angle (unit circle is now rotated half PI counterclockwise) */
    angle -= 0.5 * PI;

    /* Correct angle */
    bounds_angle(&angle);

    return (unit_circle_upper_lower(angle));
}