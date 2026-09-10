#include <pch.h>
#include "Terrain/TerrainAnalysis.h"
#include "Terrain/MapMath.h"
#include "Agent/AStarAgent.h"
#include "Terrain/MapLayer.h"
#include "Projects/ProjectThree.h"

#include <iostream>

bool ProjectThree::implemented_fog_of_war() const // extra credit
{
    return false;
}

float distance_to_closest_wall(int row, int col)
{
    /*  Check the euclidean distance from the given cell to every other wall cell,
        with cells outside the map bounds treated as walls, and return the smallest
        distance.  Make use of the is_valid_grid_position and is_wall member
        functions in the global terrain to determine if a cell is within map bounds
        and a wall, respectively. */
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();

    float closest = D3D11_FLOAT32_MAX;

        for (int i = -1; i <= height; i++)
        {
            for (int j = -1; j <= width; j++)
            {
                if (!terrain->is_valid_grid_position(i, j) || terrain->is_wall(i, j))
                {
                    float RowDiff = (float)(row - i);
                    float ColDiff = (float)(col - j);
                    float distance = std::sqrt((RowDiff * RowDiff) + (ColDiff * ColDiff));
                    if (distance < closest)
                    {
                        closest = distance;
                    }
                }
            }
        }

    return closest;
}

bool is_clear_path(int row0, int col0, int row1, int col1)
{
    /*
        Two cells (row0, col0) and (row1, col1) are visible to each other if a line
        between their centerpoints doesn't intersect the four boundary lines of every
        wall cell.  You should puff out the four boundary lines by a very tiny amount
        so that a diagonal line passing by the corner will intersect it.  Make use of the
        line_intersect helper function for the intersection test and the is_wall member
        function in the global terrain to determine if a cell is a wall or not.
    */

    // WRITE YOUR CODE HERE
    //make starting points. 
    Vec2 start = { ((float)row0), ((float)col0) };
    Vec2 end = { (float)row1, (float)col1 };
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();
    int xMin = std::min(row0, row1); int xMax = std::max(row0, row1);
    int yMin = std::min(col0, col1); int yMax = std::max(col0, col1);
    if (terrain->is_wall(row0, col0) || terrain->is_wall(row1, col1))
    {
        return false;
    }
    for (int i = xMin; i <= xMax; i++)
    {
        for (int j = yMin; j <= yMax; j++)
        {
            if (terrain->is_wall(i, j))
            {
                if (terrain->is_valid_grid_position(i, j))
                {
                    Vec2 topLeft = { i + .51f,j - .51f };
                    Vec2 topRight = { i + .51f, j + .51f };
                    Vec2 bottomLeft = { i - .51f,j - .51f };
                    Vec2 bottomRight = { i - .51f,j + .51f };

                    if (line_intersect(start, end, topLeft, topRight))
                    {
                        return false;
                    }
                    else if (line_intersect(start, end, bottomLeft, bottomRight))
                    {
                        return false;
                    }
                    else if (line_intersect(start, end, topLeft, bottomLeft))
                    {
                        return false;
                    }
                    else if (line_intersect(start, end, topRight, bottomRight))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true; 
}

void analyze_openness(MapLayer<float> &layer)
{
    /*
        Mark every cell in the given layer with the value 1 / (d * d),
        where d is the distance to the closest wall or edge.  Make use of the
        distance_to_closest_wall helper function.  Walls should not be marked.
    */
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           float d = distance_to_closest_wall(i, j);
           float mark = 1.0f / (d * d);
           layer.set_value(i, j, mark);
        }
    }
    
}

void analyze_visibility(MapLayer<float> &layer)
{
    /*
        Mark every cell in the given layer with the number of cells that
        are visible to it, divided by 160 (a magic number that looks good).  Make sure
        to cap the value at 1.0 as well.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (terrain->is_wall(i, j))
            {
                layer.set_value(i, j, 0.0f);
                continue;
            }

            int count = 0;

            if (terrain->is_valid_grid_position(i, j))
            {
                for (int i2 = 0; i2 < height && count < 160; i2++)
                {
                    for (int j2 = 0; j2 < width && count < 160; j2++)
                    {
                        if (terrain->is_valid_grid_position(i2, j2))
                        {
                            if (!terrain->is_wall(i2, j2) && is_clear_path(i, j, i2, j2))
                            {
                                count++;
                            }
                        }

                    }
                }
                float value = (float)count / 160.0f;
                if (value > 1.0f)
                {
                    value = 1.0f;
                }
                layer.set_value(i, j, value);
            }
            
        }
    }
    // WRITE YOUR CODE HERE
}

void analyze_visible_to_cell(MapLayer<float> &layer, int row, int col)
{
    /*
        For every cell in the given layer mark it with 1.0
        if it is visible to the given cell, 0.5 if it isn't visible but is next to a visible cell,
        or 0.0 otherwise.

        Two cells are visible to each other if a line between their centerpoints doesn't
        intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
        helper function.
    */
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (terrain->is_wall(i, j))
            {
                layer.set_value(i, j, 0.0f);
                continue;
            }
            if (is_clear_path(i, j, row, col))
            {
                layer.set_value(i, j, 1.0f);
            }
            else 
            {
                bool check = false;
                for (int neighbori = -1; neighbori <= 1; neighbori++)
                {
                    for (int neighborj = -1; neighborj <= 1; neighborj++)
                    {
                        if (neighbori == 0 && neighborj == 0)
                            continue;
                        
                        if (!terrain->is_valid_grid_position(i + neighbori, j + neighborj))
                        {
                            continue;
                        }
                        if (terrain->is_wall(i + neighbori, j + neighborj))
                        {
                            continue;
                        }
                        if (!is_clear_path(i,j, i + neighbori, j + neighborj ))
                        {
                            continue;
                        }

                            if (is_clear_path(i + neighbori, j + neighborj, row, col))
                            {
                                
                                check = true;
                                
                                break;
                            }
                        
                    }
                    if (check == true)
                        break;
                }
                if (check)
                {
                    layer.set_value(i, j, 0.5f);
                }
                else
                {
                    layer.set_value(i, j, 0.0f);
                }
            }
        
        }
    }
    // WRITE YOUR CODE HERE
}

void analyze_agent_vision(MapLayer<float>& layer, const Agent* agent)
{
   /*
    For every cell in the given layer that is visible to the given agent, mark it as 1.0, otherwise don't change the cell's current value.

    You must consider the direction the agent is facing.All of the agent data is
    in three dimensions, but to simplify you should operate in two dimensions, the XZ plane.

    Take the dot product between the view vector and the vector from the agent to the cell,
    both normalized, and compare the cosines directly instead of taking the arccosine to
    avoid introducing floating - point inaccuracy(larger cosine means smaller angle).

    Give the agent a field of view slighter larger than 180 degrees.

    Two cells are visible to each other if a line between their centerpoints doesn't
    intersect the four boundary lines of every wall cell.Make use of the is_clear_path
    helper function.
    */


    int height = terrain->get_map_height();
    int width = terrain->get_map_width();
    GridPos agentP = terrain->get_grid_position(agent->get_position());
    Vec2 viewVec(agent->get_forward_vector().x, agent->get_forward_vector().z);
    viewVec.Normalize();
    Vec3 agentWorldPos = agent->get_position();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (terrain->is_wall(i, j))
            {
                continue;
            }

            GridPos cellPos;
            cellPos.row = i;
            cellPos.col = j;

            Vec3 cellWorldPos = terrain->get_world_position(cellPos);
            Vec2 agent(cellWorldPos.x - agentWorldPos.x,cellWorldPos.z - agentWorldPos.z);

            if (agent.x == 0.0f && agent.y == 0.0f)
            {
                layer.set_value(i, j, 1.0f);
                continue;
            }

            agent.Normalize();

            float result = viewVec.Dot(agent);
            if (result > -0.099f)
            {
                if (is_clear_path(i, j, agentP.row, agentP.col))
                {
                    layer.set_value(i, j, 1.0f);
                }
            }
        }
    }
}

void propagate_solo_occupancy(MapLayer<float> &layer, float decay, float growth)
{
    /*
        For every cell in the given layer:

            1) Get the value of each neighbor and apply decay factor
            2) Keep the highest value from step 1
            3) Linearly interpolate from the cell's current value to the value from step 2
               with the growing factor as a coefficient.  Make use of the lerp helper function.
            4) Store the value from step 3 in a temporary layer.
               A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

        After every cell has been processed into the temporary layer, write the temporary layer into
        the given layer;
    */
    
    // WRITE YOUR CODE HERE

    int height = terrain->get_map_height();
    int width = terrain->get_map_width();
    float temp[40][40];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float dist = 0;
            if (terrain->is_wall(i, j))
            {
                temp[i][j] = 0.0f;
                continue;
            }
            // 1) Get the value of each neighbor and apply decay factor
            float big = 0;
            for (int neighbori = -1; neighbori <= 1; neighbori++)
            {
                for (int neighborj = -1; neighborj <= 1; neighborj++)
                {
                    if (neighbori == 0 && neighborj == 0)
                        continue;
                    if (!terrain->is_valid_grid_position(i + neighbori, j + neighborj))
                        continue;
                    if (terrain->is_wall(i + neighbori, j + neighborj))
                        continue;
                    if (neighbori != 0 && neighborj != 0)
                    {
                        if (terrain->is_wall(i + neighbori, j) || terrain->is_wall(i, j + neighborj))
                        {
                            continue;
                        }
                    }
                    float distance = 1.0f;
                    if (neighbori != 0 && neighborj != 0)
                    {
                        distance = sqrt(2);
                    }
                    float Influ = layer.get_value(i + neighbori, j + neighborj) * std::exp(-1.0f * distance * decay);
                    if (Influ > big)
                    {
                        big = Influ;
                        
                    }

                }
            }
            temp[i][j] = lerp(layer.get_value(i, j), big, growth);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            layer.set_value(i, j, temp[i][j]);
        }
    }
}

void normalize_solo_occupancy(MapLayer<float> &layer)
{
    /*
        Determine the maximum value in the given layer, and then divide the value
        for every cell in the layer by that amount.  This will keep the values in the
        range of [0, 1].  Negative values should be left unmodified.
    */
    
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();
    float best = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float temp = layer.get_value(i, j);
            if (best < temp)
            {
                best = temp;
            }
        }
    }
    if (best == 0) return; //don't divide by zero, it made issac neuton die.
    for (int i2 = 0; i2 < height; i2++)
    {
        for (int j2 = 0; j2 < width; j2++)
        {
            if (layer.get_value(i2, j2) < 0)
            {
                continue;
            }
            layer.set_value(i2, j2, (layer.get_value(i2, j2) / best));
        }
    }
}

void enemy_field_of_view(MapLayer<float> &layer, float fovAngle, float closeDistance, float occupancyValue, AStarAgent *enemy)
{
    /*
        First, clear out the old values in the map layer by setting any negative value to 0.
        Then, for every cell in the layer that is within the field of view cone, from the
        enemy agent, mark it with the occupancy value.  Take the dot product between the view
        vector and the vector from the agent to the cell, both normalized, and compare the
        cosines directly instead of taking the arccosine to avoid introducing floating-point
        inaccuracy (larger cosine means smaller angle).

        If the tile is close enough to the enemy (less than closeDistance),
        you only check if it's visible to enemy.  Make use of the is_clear_path
        helper function.  Otherwise, you must consider the direction the enemy is facing too.
        This creates a radius around the enemy that the player can be detected within, as well
        as a fov cone.
    */
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();
    Vec2 viewVec(enemy->get_forward_vector().z, enemy->get_forward_vector().x);
    viewVec.Normalize();
    GridPos agentP = terrain->get_grid_position(enemy->get_position());
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (layer.get_value(i, j) < 0)
                layer.set_value(i, j, 0);

            if (terrain->is_wall(i, j))
            {
                continue;
            }

            float rDiff = (float)(i - agentP.row);
            float cDiff = (float)(j - agentP.col);
            float distance = std::sqrt((rDiff * rDiff) + (cDiff * cDiff));
            if (distance < closeDistance)
            {
                if (is_clear_path(i, j, agentP.row, agentP.col))
                {
                    layer.set_value(i, j, occupancyValue);
                    continue;
                }
            }
            
            
            if ((float)i - agentP.row == 0.0f && (float)j - agentP.col == 0.0f)
            {
                continue;
            }
            Vec2 agent((float)(j - agentP.col), (float)(i - agentP.row));
            agent.Normalize();
            float result = viewVec.Dot(agent);
            float cosfov = std::cosf(fovAngle / 2.0f);
            if (result > cosfov)
            {
                if (is_clear_path(i, j, agentP.row, agentP.col))
                {
                    layer.set_value(i, j, occupancyValue);
                }
            }
        }
    }
}

bool enemy_find_player(MapLayer<float> &layer, AStarAgent *enemy, Agent *player)
{
    /*
        Check if the player's current tile has a negative value, ie in the fov cone
        or within a detection radius.
    */

    const auto &playerWorldPos = player->get_position();

    const auto playerGridPos = terrain->get_grid_position(playerWorldPos);

    // verify a valid position was returned
    if (terrain->is_valid_grid_position(playerGridPos) == true)
    {
        if (layer.get_value(playerGridPos) < 0.0f)
        {
            return true;
        }
    }

    // player isn't in the detection radius or fov cone, OR somehow off the map
    return false;
}

bool enemy_seek_player(MapLayer<float> &layer, AStarAgent *enemy)
{
    /*
        Attempt to find a cell with the highest nonzero value (normalization may
        not produce exactly 1.0 due to floating point error), and then set it as
        the new target, using enemy->path_to.

        If there are multiple cells with the same highest value, then pick the
        cell closest to the enemy.

        Return whether a target cell was found.
    */
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();
    float best = 0;
    float bestDist = 9999999;
    GridPos enemyPos = terrain->get_grid_position(enemy->get_position());
    Vec2 cell;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int value = layer.get_value(i, j);
            if (value == best)
            {
                
                float dist = Vec2::Distance(Vec2(cell.x, cell.y), Vec2(enemyPos.row, enemyPos.col));
                if (dist < bestDist)
                {
                    cell = { (float)i,(float)j };
                    bestDist = dist;
                }
            }
            else if (value > best)
            {
                best = value;
                cell = { (float)i,(float)j };
            }
        }
    }
    if (best == 0)
    {
        return false;
    }
    GridPos target;
    target.row = cell.x;
    target.col = cell.y;
    enemy->path_to(terrain->get_world_position(target));
    

    return true; 
}
