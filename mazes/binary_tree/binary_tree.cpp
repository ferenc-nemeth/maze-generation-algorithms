/**
 * @file    binary_tree.cpp
 * @author  Ferenc Nemeth
 * @date    18 Nov 2018
 * @brief   Maze generator class with binary tree algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "binary_tree.h"

/**
 * @brief   This method generates the maze with binary tree algorithm.
 * @param   void
 * @return  void
 */
void maze::binary_tree::generate(void)
{
  /* Mersenne Twister 19937 pseudo-random generator. */
  std::mt19937 random_generator(random_device());
  std::uniform_int_distribution<uint32_t> random_dir(vertical, horizontal);

  uint32_t orientation = none;

  /* Loop through vertically. */
  for (uint32_t y = 1u; y < (area.size()-1u); y += 2)
  {
    /* Loop through horizontally. */
    for (uint32_t x = 1u; x < (area[0u].size()-1u); x += 2)
    {
      /* If we are at the end (vertically or horizontally), then we can only go to the other direction. */
      /* Or if we are the end in both cases, then skip the last step. */
      if (((area[0u].size()-2u) == x) && ((area.size()-2u) == y))
      {
        orientation = none;
      }
      else if ((area[0u].size()-2u) == x)
      {
        orientation = horizontal;
      }
      else if ((area.size()-2u) == y)
      {
        orientation = vertical;
      }      
      /* If we aren't at the end, then randomly select a direction. */
      else
      {
        orientation = random_dir(random_generator); 
      }
      
      if (vertical == orientation)
      {
        /* Crave a passage 3 steps down. */
        for (uint32_t i = 0u; i < 3u; i++)
        {
          area[y][x+i] = hole;
        }
      }
      else if (horizontal == orientation)
      {
        /* Crave a passage 3 steps left. */
        for (uint32_t i = 0u; i < 3u; i++)
        {
          area[y+i][x] = hole;
        }
      }
      else
      {
        /* Do nothing. */
      }
    }
  }
}

