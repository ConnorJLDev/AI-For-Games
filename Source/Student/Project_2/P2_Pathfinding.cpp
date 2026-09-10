#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"


#pragma region Extra Credit 
bool ProjectTwo::implemented_floyd_warshall()
{
    return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
    return false;
}
#pragma endregion

bool AStarPather::initialize()
{
    // handle any one-time setup requirements you have

    /*
        If you want to do any map-preprocessing, you'll need to listen
        for the map change message.  It'll look something like this:

        Callback cb = std::bind(&AStarPather::your_function_name, this);
        Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

        There are other alternatives to using std::bind, so feel free to mix it up.
        Callback is just a typedef for std::function<void(void)>, so any std::invoke'able
        object that std::function can wrap will suffice.
    */

    Callback cb = std::bind(&AStarPather::resetmap, this);
    Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

    return true; // return false if any errors actually occur, to stop engine initialization

}

void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */
}

void AStarPather::resetmap()
{
    int height = terrain->get_map_height();
    int width = terrain->get_map_width();

    map.clear();
    map.resize(height);

    for (int i = 0; i < height; i++)
    {
        map[i].resize(width);
    }

    open.clear();
    open.resize(width * height, nullptr);

    for (int i = 0; i < terrain->get_map_height(); i++)
    {
        for (int j = 0; j < terrain->get_map_width(); j++)
        {
            map[i][j].x = j;
            map[i][j].y = i;
            map[i][j].parent = nullptr;

            map[i][j].neighbors = { false, false, false, false, false, false, false, false };

            int tempindex = 0;

            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    if (x == 0 && y == 0)
                        continue;

                    int neighborX = j + x;
                    int neighborY = i + y;

                    if (neighborX < 0 || neighborX >= terrain->get_map_width() ||
                        neighborY < 0 || neighborY >= terrain->get_map_height())
                    {
                        map[i][j].neighbors[tempindex] = true;
                    }
                    else if (terrain->is_wall(neighborY, neighborX))
                    {
                        map[i][j].neighbors[tempindex] = true;
                    }

                    tempindex++;
                }
            }
        }
    }
}

float AStarPather::calculate_heuristic(int x, int y, Heuristic heuristic)
{
    switch (heuristic) 
    {
    case Heuristic::NUM_ENTRIES:
        break;
    case Heuristic::CHEBYSHEV:
        return std::max(std::abs(x - goal.row),std::abs(y - goal.col));
      
    case Heuristic::MANHATTAN:
        return std::abs(x - goal.row) + std::abs(y - goal.col);
    
    case Heuristic::EUCLIDEAN:
        return std::sqrt(std::pow(x - goal.row,2)+ std::pow(y - goal.col,2));
    
    case Heuristic::INCONSISTENT:
        if ((x + y) % 2 > 0)
        {
            return std::sqrt(std::pow(x - goal.row, 2) + std::pow(y - goal.col, 2));
        }
        return 0;
        
    case Heuristic::OCTILE:
        return std::min(std::abs(x - goal.row), std::abs(y - goal.col)) * std::sqrt(2.0) + std::max(std::abs(x - goal.row), std::abs(y - goal.col)) - std::min(std::abs(x - goal.row), std::abs(y - goal.col));
      
    }
}

bool AStarPather::can_rubberband(const GridPos& start, const GridPos& end)
{
    int minRow = std::min(start.row, end.row);
    int maxRow = std::max(start.row, end.row);

    int minCol = std::min(start.col, end.col);
    int maxCol = std::max(start.col, end.col);

    for (int row = minRow; row <= maxRow; row++)
    {
        for (int col = minCol; col <= maxCol; col++)
        {
            if (terrain->is_wall(row, col))
            {
                return false;
            }
        }
    }

    return true;
}
void AStarPather::rubber_band_path(std::vector<GridPos>& path)
{
    if (path.size() < 3)
    {
        return;
    }

    std::vector<GridPos> rubberPath;

    int anchor = 0;
    rubberPath.push_back(path[anchor]);

    for (int test = 2; test < path.size(); test++)
    {
        if (can_rubberband(path[anchor], path[test]) == false)
        {
            rubberPath.push_back(path[test - 1]);
            anchor = test - 1;
        }
    }

    rubberPath.push_back(path.back());

    path = rubberPath;
}
void AStarPather::smooth_path(std::vector<Vec3>& path)
{
    if (path.size() < 2)
    {
        return;
    }

    std::vector<Vec3> smoothPath;

    for (int i = 0; i < path.size() - 1; i++)
    {
        Vec3 p0;
        Vec3 p1;
        Vec3 p2;
        Vec3 p3;

        if (i == 0)
        {
            p0 = path[i];
        }
        else
        {
            p0 = path[i - 1];
        }

        p1 = path[i];
        p2 = path[i + 1];

        if (i + 2 >= path.size())
        {
            p3 = path[i + 1];
        }
        else
        {
            p3 = path[i + 2];
        }

        smoothPath.push_back(p1);
        smoothPath.push_back(Vec3::CatmullRom(p0, p1, p2, p3, 0.25f));
        smoothPath.push_back(Vec3::CatmullRom(p0, p1, p2, p3, 0.50f));
        smoothPath.push_back(Vec3::CatmullRom(p0, p1, p2, p3, 0.75f));
    }

    smoothPath.push_back(path.back());

    path = smoothPath;
}
void AStarPather::addPoints(std::vector<GridPos>& rubberbandedGridPath, std::vector<Vec3>& outWorldPath)
{
    outWorldPath.clear();

    if (rubberbandedGridPath.size() < 2)
    {
        for (auto& gp : rubberbandedGridPath)
            outWorldPath.push_back(terrain->get_world_position(gp));
        return;
    }

    outWorldPath.push_back(terrain->get_world_position(rubberbandedGridPath[0]));

    for (size_t i = 0; i < rubberbandedGridPath.size() - 1; i++)
    {
        const GridPos& startGrid = rubberbandedGridPath[i];
        const GridPos& endGrid = rubberbandedGridPath[i + 1];

        // Distance measured in GRID UNITS (row/col space), not world space.
        float dRow = static_cast<float>(endGrid.row - startGrid.row);
        float dCol = static_cast<float>(endGrid.col - startGrid.col);
        float gridDistance = std::sqrt(dRow * dRow + dCol * dCol);

        // Only subdivide if the gap is MORE than 1.5 grid units (per slide 117-123).
        int pieces = static_cast<int>(std::ceil(gridDistance / 1.5f));
        if (pieces < 1)
        {
            pieces = 1;
        }

        Vec3 startWorld = terrain->get_world_position(startGrid);
        Vec3 endWorld = terrain->get_world_position(endGrid);

        for (int j = 1; j < pieces; j++)
        {
            float t = static_cast<float>(j) / static_cast<float>(pieces);

            Vec3 newPoint;
            newPoint.x = startWorld.x + (endWorld.x - startWorld.x) * t;
            newPoint.y = startWorld.y + (endWorld.y - startWorld.y) * t;
            newPoint.z = startWorld.z + (endWorld.z - startWorld.z) * t;

            outWorldPath.push_back(newPoint);
        }

        outWorldPath.push_back(endWorld);
    }
}


PathResult AStarPather::compute_path(PathRequest &request)
{
    /*
        This is where you handle pathing requests, each request has several fields:

        start/goal - start and goal world positions
        path - where you will build the path upon completion, path should be
            start to goal, not goal to start
        heuristic - which heuristic calculation to use
        weight - the heuristic weight to be applied
        newRequest - whether this is the first request for this path, should generally
            be true, unless single step is on

        smoothing - whether to apply smoothing to the path
        rubberBanding - whether to apply rubber banding
        singleStep - whether to perform only a single A* step
        debugColoring - whether to color the grid based on the A* state:
            closed list nodes - yellow
            open list nodes - blue

            use terrain->set_color(row, col, Colors::YourColor);
            also it can be helpful to temporarily use other colors for specific states
            when you are testing your algorithms

        method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
            will be A* generally, unless you implement extra credit features

        The return values are:
            PROCESSING - a path hasn't been found yet, should only be returned in
                single step mode until a path is found
            COMPLETE - a path to the goal was found and has been built in request.path
            IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path
    */

    // WRITE YOUR CODE HERE
    if (request.newRequest)
    {
        request.path.clear();

        if (map.empty())
        {
            resetmap();
        }

        int height = terrain->get_map_height();
        int width = terrain->get_map_width();

        if (map.size() != height || map[0].size() != width)
        {
            resetmap();
        }

        //reset array of path
        for (int i = 0; i < open.size(); i++)
        {
            open[i] = nullptr;
        }

        open_index = -1;

        //reset path
        for (int i = 0; i < terrain->get_map_height(); i++)
        {
            for (int j = 0; j < terrain->get_map_width(); j++)
            {
                map[i][j].travel = traveled::NOT_VISITED;
                map[i][j].parent = nullptr;
                map[i][j].G_cost = 0;
                map[i][j].F_cost = 0;
            }
        }


        //1. create start position
        start = terrain->get_grid_position(request.start);
        goal = terrain->get_grid_position(request.goal);
        map[start.row][start.col].F_cost = calculate_heuristic(start.row, start.col, request.settings.heuristic);
        map[start.row][start.col].G_cost = 0;
        map[start.row][start.col].travel = traveled::VISITED;
        open[++open_index] = &map[start.row][start.col];
        if (request.settings.debugColoring == true)
        {
            terrain->set_color(start, Colors::Blue);
        }
    }
        //1.5 While (Open List is not empty) {
        while (open_index >= 0)
        {
  
            int cheapest = 0;
            //2. parentNode = Pop cheapest node off Open List(call Pop() on Open List).
            //find cheapest 
            for (int i = 0; i <= open_index; i++)
            {
                if (open[i] == nullptr)
                    continue;
                if (open[i]->F_cost < open[cheapest]->F_cost)
                    cheapest = i; 
            }
            
            Tile* parent = open[cheapest];

            // Remove cheapest node from open list
            for (int i = cheapest; i < open_index; i++)
            {
                open[i] = open[i + 1];
            }

            open[open_index] = nullptr;
            open_index--;


            //If parentNode is the Goal Node, then path found (return PathResult::COMPLETE).
            if (parent->y == goal.row && parent->x == goal.col)
            {
                std::vector<GridPos> currentPath;

                Tile* current = parent;

                while (current != nullptr)
                {
                    GridPos pos;
                    pos.row = current->y;
                    pos.col = current->x;

                    currentPath.push_back(pos);

                    current = current->parent;
                }

                // We built the path from goal to start, so reverse it.
                std::reverse(currentPath.begin(), currentPath.end());
                request.path.clear();

                if (request.settings.rubberBanding == false && request.settings.smoothing == false)
                {
                    for (int i = 0; i < currentPath.size(); i++)
                    {
                        request.path.push_back(terrain->get_world_position(currentPath[i]));
                    }

                    return PathResult::COMPLETE;
                }
                else if (request.settings.rubberBanding == true && request.settings.smoothing == false)
                {
                    rubber_band_path(currentPath);

                    for (int i = 0; i < currentPath.size(); i++)
                    {
                        request.path.push_back(terrain->get_world_position(currentPath[i]));
                    }

                    return PathResult::COMPLETE;
                }
                else if (request.settings.rubberBanding == false && request.settings.smoothing == true)
                {
                    std::vector<Vec3> smoothingPath;

                    for (int i = 0; i < currentPath.size(); i++)
                    {
                        smoothingPath.push_back(terrain->get_world_position(currentPath[i]));
                    }

                    smooth_path(smoothingPath);

                    for (int i = 0; i < smoothingPath.size(); i++)
                    {
                        request.path.push_back(smoothingPath[i]);
                    }

                    return PathResult::COMPLETE;
                }
                else if (request.settings.rubberBanding == true && request.settings.smoothing == true)
                {
                    rubber_band_path(currentPath);

                    // If rubberbanding reduced the path to one straight shot,
                    // do NOT add points or smooth. Just use the rubberbanded path.
                    if (currentPath.size() == 2)
                    {
                        for (int i = 0; i < currentPath.size(); i++)
                        {
                            request.path.push_back(terrain->get_world_position(currentPath[i]));
                        }

                        return PathResult::COMPLETE;
                    }

                    // Otherwise, the path still has turns/corners, so add points back in
                    // and then smooth those sections.
                    std::vector<Vec3> smoothingPath;

                    addPoints(currentPath, smoothingPath);

                    smooth_path(smoothingPath);

                    for (int i = 0; i < smoothingPath.size(); i++)
                    {
                        request.path.push_back(smoothingPath[i]);
                    }

                    return PathResult::COMPLETE;
                }
            }
            //For (all neighboring child nodes of parentNode) {
            for (int j = -1; j <= 1; j++)
            {
                for (int k = -1; k <= 1; k++)
                {
                    if (j == 0 && k == 0)
                        continue;

                    int childpos[2] = { (parent->x + k), (parent->y + j)};

                    // Bounds check
                    if (childpos[0] < 0 || childpos[0] >= terrain->get_map_width() ||
                        childpos[1] < 0 || childpos[1] >= terrain->get_map_height())
                    {
                        continue;
                    }
                    // Wall check
                    if (terrain->is_wall(childpos[1], childpos[0]))
                    {
                        continue;
                    }
                    // Prevent cutting diagonally through walls
                    if (j != 0 && k != 0)
                    {
                        if (terrain->is_wall(parent->y, parent->x + k) ||
                            terrain->is_wall(parent->y + j, parent->x))
                        {
                            continue;
                        }
                    }
                    //Get tile of child
                    Tile* child = &map[childpos[1]][childpos[0]];
                    //Move cost calculation
                    float moveCost = 1.0f;
                    // Diagonal movement costs more
                    if (j != 0 && k != 0)
                    {
                        moveCost = 1.414f;
                    }
                    float gcost = parent->G_cost + moveCost; 
                    //If child node isn’t on Open or Closed list, put it on Open List (call Push() on Open List).
                    if (child->travel == traveled::NOT_VISITED)
                    {
                        child->G_cost = gcost;
                        child->F_cost = gcost + request.settings.weight * calculate_heuristic(child->y, child->x, request.settings.heuristic);

                        child->parent = parent;
                        child->travel = traveled::VISITED;
                        open[++open_index] = child;

                        //Color it
                        if (request.settings.debugColoring)
                        {
                            terrain->set_color({ child->y,child->x }, Colors::Blue);
                        }
                    }
                    //Else if child node is on Open or Closed List, AND this new one is cheaper (use g(x)),
                    else if ((child->travel == traveled::VISITED || child->travel == traveled::CLOSED) && gcost < child->G_cost)
                    {
                        //then take the old expensive one off both lists and put this new
                        child->G_cost = gcost;
                        child->F_cost = gcost + request.settings.weight * calculate_heuristic(child->y, child->x, request.settings.heuristic);
                        child->parent = parent;

                        //cheaper one on the Open List (call Update() on Open List).
                        if (child->travel == traveled::CLOSED)
                        {
                            child->travel = traveled::VISITED;
                            open[++open_index] = child;

                            if (request.settings.debugColoring)
                            {
                                terrain->set_color({ child->y, child->x }, Colors::Yellow);
                            }
                        }

                    }
                }
            }
            parent->travel = traveled::CLOSED;
            //Color it
            if (request.settings.debugColoring)
            {
                terrain->set_color({ parent->y,parent->x }, Colors::Yellow);
            }

            if (request.settings.singleStep)
            {
                return PathResult::PROCESSING;
            }
        }

        return PathResult::IMPOSSIBLE;
    }
    /*

While (Open List is not empty) {
parentNode = Pop cheapest node off Open List (call Pop() on Open List).
If parentNode is the Goal Node, then path found (return PathResult::COMPLETE).
For (all neighboring child nodes of parentNode) {
If child node isn’t on Open or Closed list, put it on Open List (call Push() on Open List).
Else if child node is on Open or Closed List, AND this new one is cheaper (use g(x)),
	then take the old expensive one off both lists and put this new
 	cheaper one on the Open List (call Update() on Open List).
(If adding to Open list: Compute its cost, f(x) = g(x) + h(x), set new Parent Pointer!)
}
Place parentNode on the Closed List.
If taken too much time this frame (or if request.settings.singleStep == true), 
	 abort search for now and resume next frame (return PathResult::PROCESSING).
}
Open List empty, thus no path possible (return PathResult::IMPOSSIBLE).

    
    */


    
   

