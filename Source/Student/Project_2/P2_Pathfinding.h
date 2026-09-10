#pragma once
#include "Misc/PathfindingDetails.hpp"

class AStarPather
{
public:
    /* 
        The class should be default constructible, so you might need to define a constructor.
        If needed, you can modify the framework where the class is constructed in the
        initialize functions of ProjectTwo and ProjectThree.
    */
    
    /* ************************************************** */
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    void resetmap();
    float calculate_heuristic(int x, int y, Heuristic heuristic);
    bool can_rubberband(const GridPos& start, const GridPos& end);
    void rubber_band_path(std::vector<GridPos>& path);
    void smooth_path(std::vector<Vec3>& path);
    void addPoints(std::vector<GridPos>& rubberbandedGridPath, std::vector<Vec3>& outWorldPath);

    PathResult compute_path(PathRequest &request);
    /* ************************************************** */

    /*
        You should create whatever functions, variables, or classes you need.
        It doesn't all need to be in this header and cpp, structure it whatever way
        makes sense to you.
    */
    enum class traveled {
        NOT_VISITED,
        VISITED,
        CLOSED
    };

    struct Tile
    {
        int x;
        int y;
        float F_cost;
        float G_cost;
        std::array<bool,8> neighbors;
        traveled travel;
        Tile* parent;
    };
public:
    std::vector<std::vector<Tile>> map;
    std::vector<Tile*> open;

    GridPos start;
    GridPos goal;

    int open_index = -1;
};