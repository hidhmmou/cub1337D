#include "../includes/execution.h"
#include <limits.h>
float normligize_angle(float angle)
{
    angle = remainder(angle ,(2.0 * M_PI));
    if (angle < 0)
        angle += (2 * M_PI);
    return (angle);
}

float get_distance(float x1, float y1, float x2, float y2)
{
    float distance;

    distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return (distance);
}

int has_wall_at(t_cub3d *cub3d, float x, float y)
{
    int gridIndexX = floor(x / SIZE);
    int gridIndexY = floor(y / SIZE);

    if (gridIndexX < 0 || gridIndexX > cub3d->map->max_len - 1 || gridIndexY < 0 || gridIndexY > cub3d->map->len - 1)
        return (0);
    return (in_set(cub3d->map->square_map[gridIndexY][gridIndexX], "1DX"));
}

float intersect_dist(t_cub3d *cub3d)
{
    float angle;

    angle = normligize_angle(cub3d->draw->radiant + M_PI);
    int isRayFacingDown = angle > 0 && angle < M_PI;
    int isRayFacingUp = !isRayFacingDown;
    int isRayFacingRight = angle < 0.5 * M_PI || angle > 1.5 * M_PI;
    int isRayFacingLeft = !isRayFacingRight;

    float xintercept, yintercept;
    float xstep, ystep;

    int     foundHorzWallHit = 0;
    float   horzWallHitX = 0;
    float   horzWallHitY = 0;
    int     horzWallContent = 0;

    // Find the x and y intercepts
    yintercept = floor(cub3d->map->player.y / SIZE) * SIZE;
    yintercept += isRayFacingDown ? SIZE : 0;
    
    // find the x coordinate of the first (horizontal) grid intersection
    xintercept = cub3d->map->player.x + (yintercept - cub3d->map->player.y) / tan(angle);

    // calculate the increment xstep and ystep
    ystep = SIZE;
    ystep *= isRayFacingUp ? -1 : 1;

    xstep = SIZE / tan(angle);
    xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
    xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    
    // increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= (cub3d->map->max_len - 1) * SIZE && nextHorzTouchY >= 0 && nextHorzTouchY <= (cub3d->map->len - 1) * SIZE)
    {
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);
        if (has_wall_at(cub3d, xToCheck, yToCheck))
        {
            horzWallHitX = nextHorzTouchX;
            horzWallHitY = nextHorzTouchY;
            horzWallContent = cub3d->map->square_map[(int)floor(yToCheck / SIZE)][(int)floor(xToCheck / SIZE)];
            foundHorzWallHit = 1;
            break ;
        }
        else
        {
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
    }

    int     foundVertWallHit = 0;
    float   vertWallHitX = 0;
    float   vertWallHitY = 0;
    int     vertWallContent = 0;

    // Find the x and y intercepts
    xintercept = floor(cub3d->map->player.x / SIZE) * SIZE; 
    xintercept += isRayFacingRight ? SIZE : 0;

    // find the y coordinate of the first (vertical) grid intersection
    yintercept = cub3d->map->player.y + (xintercept - cub3d->map->player.x) * tan(angle);

    // calculate the increment xstep and ystep  
    xstep = SIZE;
    xstep *= isRayFacingLeft ? -1 : 1;

    ystep = SIZE * tan(angle);
    ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
    ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= cub3d->map->max_len * SIZE && nextVertTouchY >= 0 && nextVertTouchY <= cub3d->map->len * SIZE)
    {
        float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
        float yToCheck = nextVertTouchY;
        if (has_wall_at(cub3d, xToCheck, yToCheck))
        {
            vertWallHitX = nextVertTouchX;
            vertWallHitY = nextVertTouchY;
            vertWallContent = cub3d->map->square_map[(int)floor(yToCheck / SIZE)][(int)floor(xToCheck / SIZE)];
            foundVertWallHit = 1;
            break ;
        }
        else
        {
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
    }

    float horzHitDistance = foundHorzWallHit ? get_distance(cub3d->map->player.x, cub3d->map->player.y, horzWallHitX, horzWallHitY) : INT_MAX;
    float vertHitDistance = foundVertWallHit ? get_distance(cub3d->map->player.x, cub3d->map->player.y, vertWallHitX, vertWallHitY) : INT_MAX;

    if (vertHitDistance < horzHitDistance)
    {
        cub3d->map->player.direction = VERTICAL;
        cub3d->draw->wallHitX = vertWallHitX;
        cub3d->draw->wallHitY = vertWallHitY;
        cub3d->draw->wallHitContent = vertWallContent;
        return (vertHitDistance);
    }
    else
    {
        cub3d->map->player.direction = HORIZONTAL;
        cub3d->draw->wallHitX = horzWallHitX;
        cub3d->draw->wallHitY = horzWallHitY;
        cub3d->draw->wallHitContent = horzWallContent;
        return (horzHitDistance);
    }
}