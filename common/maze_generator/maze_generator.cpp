/**
 * @file    maze_generator.cpp
 * @author  Ferenc Nemeth
 * @date    3 Dec 2018
 * @brief   Base class: methods and variables used by every maze generator.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "maze_generator.h"

/**
 * @brief   Constructor. Generates a 2D vector, which represents the maze.
 * @param   height - Height of the maze.
 * @param   width  - Width of the maze.
 * @return  void
 */
maze::maze_generator::maze_generator(uint32_t height, uint32_t width)
{
  /* Make sure, that the dimensions are odd numbers, otherwise the maze would look strange. */
  if ((!(height%2u)) || (!(width%2u)))
  {
    throw std::invalid_argument("Height and width must be odd numbers!");
  }

  /* Create an area filled with walls. */
  area.resize(height);
  for (uint32_t y = 0u; y < height; y++)
  {
    area[y].resize(width);
    for (uint32_t x = 0u; x < width; x++)
    {
      area[y][x] = wall;
    }
  }
}

/**
 * @brief   Manually changes a cell to be a wall.
 * @param   y - The y coordinate of the wall.
 * @param   x - The x coordinate of the wall.
 * @return  void
 */
void maze::maze_generator::set_wall(uint32_t y, uint32_t x)
{
  if ((area.size() <= y) || (area[y].size() <= x))
  {
    throw std::invalid_argument("Out of boundary! (set_wall)");
  }
  else
  { 
    area[y][x] = wall;
  }
}

/**
 * @brief   Manually changes a cell to be a hole. This is useful for entrance/exit creation.
 * @param   y - The y coordinate of the hole.
 * @param   x - The x coordinate of the hole.
 * @return  void
 */
void maze::maze_generator::set_hole(uint32_t y, uint32_t x)
{
  if ((area.size() <= y) || (area[y].size() <= x))
  {
    throw std::invalid_argument("Out of boundary! (set_hole)");
  }
  else
  { 
    area[y][x] = hole;
  }
}

/**
 * @brief   Returns the maze.
 * @param   void
 * @return  maze - 2D vector of the maze. 1 represents a hole, 0 represents a wall.
 */
std::vector<std::vector<uint32_t>> maze::maze_generator::get_maze(void)
{
  return area;
}

