/**
 * @file    recursive_backtracking.cpp
 * @author  Ferenc Nemeth
 * @date    18 Nov 2018
 * @brief   Maze generator class with recursive backtracking algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "recursive_backtracking.h"

/**
 * @brief   This method generates the maze with recursive backtracking algorithm.
 * @param   void
 * @return  void
 */
void maze::recursive_backtracking::generate(void)
{
  /* Mersenne Twister 19937 pseudo-random generator. */
  std::mt19937 random_generator(random_device());
  /* Random starting point. */
  std::uniform_int_distribution<uint32_t> random_start_y(1u, area.size()-2u);
  std::uniform_int_distribution<uint32_t> random_start_x(1u, area[0u].size()-2u);

  /* Start the craving process. */
  /* Make sure, that the two random numbers are odd. */
  crave_passage(random_start_y(random_generator)/2u*2u+1u, random_start_x(random_generator)/2u*2u+1u);
}

/**
 * @brief   Randomly craves (creates holes) through the maze.
 * @param   void
 * @return  void
 */
void maze::recursive_backtracking::crave_passage(uint32_t y, uint32_t x)
{
  /* The 4 directions, we can go. */
  std::vector<uint32_t> directions = {north, south, west, east};
  
  /* Randomly shuffle the directions. */
  std::mt19937 random_generator(random_device());
  std::shuffle(directions.begin(), directions.end(), random_generator);

  /* Go through each direction inside the randomly filled vector. */
  for (uint32_t i = 0u; i < directions.size(); i++)
  {
    if (north == directions[i])
    {
      /* If it is possible to go north, then crave a passage and call the function again. */
      if ((y > 2u) && (wall == area[y-2u][x]))
      {
        for (uint32_t j = 0u; j < 3u; j++)
        {
          area[y-2u+j][x] = hole;
        }
        crave_passage(y-2u, x);
      }
    }
    else if (south == directions[i])
    {
      /* If it is possible to go south, then crave a passage and call the function again. */
      if (((y+2u) < (area.size()-1u)) && (wall == area[y+2u][x]))
      {
        for (uint32_t j = 0u; j < 3u; j++)
        {
          area[y+j][x] = hole;
        }
        crave_passage(y+2u, x);
      }
    }
    else if (west == directions[i])
    {
      /* If it is possible to go west, then crave a passage and call the function again. */
      if ((x > 2u) && (wall == area[y][x-2]))
      {
        for (uint32_t j = 0u; j < 3u; j++)
        {
          area[y][x-2u+j] = hole;
        }
        crave_passage(y, x-2u);
      }
    }
    else if (east == directions[i])
    {
      /* If it is possible to go east, then crave a passage and call the function again. */
      if (((x+2u) < (area[0u].size()-1u)) && (wall == area[y][x+2u]))
      {
        for (uint32_t j = 0u; j < 3u; j++)
        {
          area[y][x+j] = hole;
        }
        crave_passage(y, x+2u);
      }
    }
    else
    {
      /* Do nothing. */
    }
  }
}

