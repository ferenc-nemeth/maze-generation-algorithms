/**
 * @file    prim.cpp
 * @author  Ferenc Nemeth
 * @date    19 Nov 2018
 * @brief   Maze generator class with Prim's algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "prim.h"

/**
 * @brief   This method generates the maze with Prim's algorithm.
 * @param   void
 * @return  void
 */
void maze::prim::generate(void)
{
  /* Mersenne Twister 19937 pseudo-random generator. */
  std::mt19937 random_generator(random_device());
  /* Random starting point. */
  std::uniform_int_distribution<uint32_t> random_start_y(1u, area.size()-2u);
  std::uniform_int_distribution<uint32_t> random_start_x(1u, area[0u].size()-2u);
  /* Random direction. */
  std::uniform_int_distribution<uint32_t> random_dir(north, east);

  /* Make sure, that the two random numbers are odd. */
  mark(random_start_y(random_generator)/2u*2u+1u, random_start_x(random_generator)/2u*2u+1u);

  /* Loop until there are no frontiers left. */
  while(!frontiers.empty())
  {
    bool possible_to_crave = false;

    /* Randomly select a frontier from the list.*/
    std::uniform_int_distribution<uint32_t> random_frontier(0u, frontiers.size()-1u);
    uint32_t next_frontier = random_frontier(random_generator);
    uint32_t y = frontiers[next_frontier].y;
    uint32_t x = frontiers[next_frontier].x;
    /* Remove frontier from the list. */
    frontiers.erase(frontiers.begin()+next_frontier);

    /* Try to move to one direction (loop until we find a possible way to go). */
    while(!possible_to_crave)
    {
      uint32_t direction = random_dir(random_generator);
      if (north == direction)
      {
        /* If it is possible to go north, then crave a hole and stop the loop. */
        if ((y > 2u) && (hole == area[y-2u][x]))
        {
          possible_to_crave = true;
          area[y-1u][x] = hole;
        }
      }
      else if (south == direction)
      {
        /* If it is possible to go south, then crave a hole and stop the loop. */
        if (((y+2u) < (area.size()-1u)) && (hole == area[y+2u][x]))
        {
          possible_to_crave = true;
          area[y+1u][x] = hole;
        }
      }
      else if (west == direction)
      {
        /* If it is possible to go west, then crave a hole and stop the loop. */
        if ((x > 2u) && (hole == area[y][x-2]))
        {
          possible_to_crave = true;
          area[y][x-1u] = hole;
        }
      }
      else if (east == direction)
      {
        /* If it is possible to go east, then crave a hole and stop the loop. */
        if (((x+2u) < (area[0u].size()-1u)) && (hole == area[y][x+2u]))
        {
          possible_to_crave = true;
          area[y][x+1u] = hole;
        }
      }
    }

    /* Create new frontiers. */
    mark(y, x);
    
  }
}

/**
 * @brief   Set a hole at [y,x] coordinate and mark every possible neighboor cell as frontier.
 * @param   y - Coordinate of the new hole.
 *          x - Coordinate of the new hole.
 * @return  void
 */
void maze::prim::mark(uint32_t y, uint32_t x)
{
  /* Mark as a hole. */
  area[y][x] = hole;
  /* Save the cell at north as a frontier (if it isn't out of boundary). */
  if ((y >= 3u) && (wall == area[y-2u][x]))
  {
    area[y-2u][x] = frontier;
    frontiers.push_back({y-2u,x});
  }
  /* Save the cell at south as a frontier (if it isn't out of boundary). */
  if (((y+2u) <= area.size()-2u) && (wall == area[y+2u][x]))
  {
    area[y+2u][x] = frontier;
    frontiers.push_back({y+2u,x});
  }
  /* Save the cell at west as a frontier (if it isn't out of boundary). */
  if ((x >= 3u) && (wall == area[y][x-2u]))
  {
    area[y][x-2u] = frontier;
    frontiers.push_back({y,x-2u});
  }
  /* Save the cell at east as a frontier (if it isn't out of boundary). */
  if (((x+2u) <= area[0u].size()-2u) && (wall == area[y][x+2u]))
  {
    area[y][x+2u] = frontier;
    frontiers.push_back({y,x+2u});
  }
}

