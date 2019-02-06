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
 * @brief   Manually changes the value of a cell.
 * @param   y     - The y coordinate of the cell.
 * @param   x     - The x coordinate of the cell.
 * @param   value - The value, either 0 or 1.
 * @return  void
 */
void maze::maze_generator::set_cell(uint32_t y, uint32_t x, uint32_t value)
{
  if ((area.size() <= y) || (area[y].size() <= x))
  {
    throw std::invalid_argument("Out of boundary!");
  }
  else if ((wall != value) && (hole != value))
  {
    throw std::invalid_argument("The input can only contain 0 or 1.");
  } 
  else
  { 
    area[y][x] = value;
  }
}

/**
 * @brief   Returns the value of a cell.
 * @param   y     - The y coordinate of the hole.
 * @param   x     - The x coordinate of the hole.
 * @return  value - The actual value of the cell, either 0 or 1.
 */
uint32_t maze::maze_generator::get_cell(uint32_t y, uint32_t x)
{
  return area[y][x];
}

/**
 * @brief   Returns the maze.
 * @param   void
 * @return  area - 2D vector of the maze. 1 represents a hole, 0 represents a wall.
 */
std::vector<std::vector<uint32_t>> maze::maze_generator::get_maze(void)
{
  return area;
}

/**
 * @brief   Overwrites the current maze.
 * @param   vect - 2D vector of the maze. 1 represents a hole, 0 represents a wall.
 * @return  void
 */
void maze::maze_generator::set_maze(std::vector<std::vector<uint32_t>> vect)
{
  if ((vect.size() != area.size()) || (vect[0u].size() != area[0u].size()))
  {
    throw std::invalid_argument("Wrong size!");
  }
  else
  { 
    for (uint32_t y = 0u; y < vect.size(); y++)
    {
      for (uint32_t x = 0u; x < vect[y].size(); x++)
      {
        if ((wall != vect[y][x]) && (hole != vect[y][x]))
        {
          throw std::invalid_argument("The input can only contain 0 or 1.");
        }
        else
        {
          area[y][x] = vect[y][x];
        }
      }
    }
  }
}

/**
 * @brief   Reshapes the maze.
 * @param   height - New height of the maze.
 * @param   width  - New width of the maze.
 * @return  void
 */
void maze::maze_generator::reshape(uint32_t height, uint32_t width)
{
  /* Make sure, that the dimensions are odd numbers, otherwise the maze would look strange. */
  if ((!(height%2u)) || (!(width%2u)))
  {
    throw std::invalid_argument("Height and width must be odd numbers!");
  }

  /* Resize. */
  area.resize(height);
  for (uint32_t y = 0u; y < height; y++)
  {
    area[y].resize(width);
  }
}

/**
 * @brief   Returns the height of the maze.
 * @param   void
 * @return  height
 */
uint32_t maze::maze_generator::get_height(void)
{
  return area.size();
}

/**
 * @brief   Returns the width of the maze.
 * @param   void
 * @return  width
 */
uint32_t maze::maze_generator::get_width(void)
{
  return area[0u].size();
}

