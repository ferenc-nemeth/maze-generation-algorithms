/**
 * @file    aldous_broder.cpp
 * @author  Ferenc Nemeth
 * @date    20 Nov 2018
 * @brief   Maze generator class with Aldous-Broder algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "aldous_broder.h"

/**
 * @brief   This method generates the maze with Aldous-Broder algorithm.
 * @param   void
 * @return  void
 */
void maze::aldous_broder::generate(void)
{
  uint32_t y = 0u;
  uint32_t x = 0u;
  /* The number of the cells, that can be visited. */
  uint32_t total_cells = (area.size()/2u)*(area[0u].size()/2u);

  /* Mersenne Twister 19937 pseudo-random generator. */
  std::mt19937 random_generator(random_device());
  /* Random starting point. */
  std::uniform_int_distribution<uint32_t> random_start_y(1u, area.size()-2u);
  std::uniform_int_distribution<uint32_t> random_start_x(1u, area[0u].size()-2u);
  /* Random direction. */
  std::uniform_int_distribution<uint32_t> random_dir(north, east);

  /* Make sure, that the two random numbers are odd. */
  y = (random_start_y(random_generator)/2u*2u+1u);
  x = (random_start_x(random_generator)/2u*2u+1u);
  
  area[y][x] = hole;
  total_cells--;

  /* Loop until there are no cells left. */
  while(total_cells)
  {
    /* Randomly select a direction to move. */
    uint32_t next_cell = random_dir(random_generator);
    
    if (north == next_cell)
    {
      /* Check if it is possible to go north. */
      if (y >= 3u)
      {
        /* Save the new position. */
        y -= 2;
        /* In case the cell hasn't been visited, then change it to hole and lower the total_cell counter. */
        if (wall == area[y][x])
        {
          total_cells--;
          area[y][x] = hole;
          area[y+1u][x] = hole;
        }
      }
    }
    else if (south == next_cell)
    {
      /* Check if it is possible to go south. */
      if ((y+2u) <= area.size()-2u)
      {
        /* Save the new position. */
        y += 2;
        /* In case the cell hasn't been visited, then change it to hole and lower the total_cell counter. */
        if (wall == area[y][x])
        {
          total_cells--;
          area[y][x] = hole;
          area[y-1u][x] = hole;
        }
      }
    }
    else if (west == next_cell)
    {
      /* Check if it is possible to go west. */
      if (x >= 3u)
      {
        /* Save the new position. */
        x -= 2;
        /* In case the cell hasn't been visited, then change it to hole and lower the total_cell counter. */
        if (wall == area[y][x])
        {
          total_cells--;
          area[y][x] = hole;
          area[y][x+1u] = hole;
        }
      }
    }
    else if (east == next_cell)
    {
      /* Check if it is possible to go east. */
      if ((x+2u) <= area[0u].size()-2u)
      {
        /* Save the new position. */
        x += 2;
        /* In case the cell hasn't been visited, then change it to hole and lower the total_cell counter. */
        if (wall == area[y][x])
        {
          total_cells--;
          area[y][x] = hole;
          area[y][x-1u] = hole;
        }
      }
    }
    else
    {
      /* Do nothing. */
    }
    
  }
}

