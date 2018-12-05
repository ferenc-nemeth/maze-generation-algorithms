/**
 * @file    recursive_division.cpp
 * @author  Ferenc Nemeth
 * @date    18 Nov 2018
 * @brief   Maze generator class with recursive division algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "recursive_division.h"

/**
 * @brief   This method generates the maze with recursive divsion algorithm.
 * @param   void
 * @return  void
 */
void maze::recursive_division::generate(void)
{
  /* Overwrite the center with holes, so the area is going to be an empty place with wall boundaries. */
  for (uint32_t y = 1u; y < (area.size()-1u); y++)
  {
    for (uint32_t x = 1u; x < (area[0u].size()-1u); x++)
    {
      area[y][x] = hole;
    }
  }

  /* Start to divide the area. */
  divide(0u, 0u, area.size(), area[0u].size());
}

/**
 * @brief   Randomly places a wall across two borders.
 *          Randomly place a hole on the wall.
 * @param   y       - Origin point (y) of where the wall and hole can be placed.
 *          x       - Origin point (x) of where the wall and hole can be placed.
 *          height  - End point (y) of where the wall and hole can be placed.
 *          width   - End point (x) of where the wall and hole can placed.
 * @return  vod
 */
void maze::recursive_division::divide(uint32_t y, uint32_t x, uint32_t height, uint32_t width)
{  
  /*  Mersenne Twister 19937 pseudo-random generator. */
  std::mt19937 random_generator(random_device());

  uint32_t orientation = horizontal;
  uint32_t new_wall = 0u;
  uint32_t new_hole = 0u;
  uint32_t new_height = 0u;
  uint32_t new_width = 0u;
  uint32_t y_pair = 0u;
  uint32_t x_pair = 0u;
  uint32_t new_height_pair = 0u;
  uint32_t new_width_pair = 0u;

  /* Decide which orientation the wall should be. */ 
  /* If one of the is longer, then use the opposite. */ 
  /* If they are the same length, then use a random orientation. */
  if (width < height)
  {
    orientation = horizontal;
  }
  else if (width > height)
  {
    orientation = vertical;
  }
  else
  {
    std::uniform_int_distribution<uint32_t> random_dir(vertical, horizontal);
    orientation = random_dir(random_generator);
  }

  if (horizontal == orientation)
  {
    /* Not enough space, stop. */
    if (height < 5u)
    {
      return;
    }

    /* Random place for the wall and for the hole. */
    std::uniform_int_distribution<uint32_t> random_wall(2u, height-3u);
    std::uniform_int_distribution<uint32_t> random_hole(1u, width-2u);
    /* Make sure, that the wall is on an even coordinate and the hole is on an odd coordinate. */
    new_wall = y + (random_wall(random_generator)/2u*2u);
    new_hole = x + (random_hole(random_generator)/2u*2u+1u);

    /* Place the wall. */
    for (uint32_t i = x; i < (x+width-1u); i++)
    {
      area[new_wall][i] = wall;
    }
    /* Place the hole. */
    area[new_wall][new_hole] = hole;
    
    /* Calculate the new values for the next run. */
    new_height = new_wall-y+1u;
    new_width = width;
    /* Complementary pairs. 'The other side of the wall.' */
    y_pair = new_wall;
    x_pair = x;
    new_height_pair = y+height-new_wall;
    new_width_pair = width;
  }
  else if (vertical == orientation)
  {
    /* Not enough space, stop. */
    if (width < 5u)
    {
      return;
    }

    /* Random place for the wall and for the hole. */
    std::uniform_int_distribution<uint32_t> random_wall(2u, width-3u);
    std::uniform_int_distribution<uint32_t> random_hole(1u, height-2u);
    /* Make sure, that the wall is on an even coordinate and the hole is on an odd coordinate. */
    new_wall = x + (random_wall(random_generator)/2u*2u);
    new_hole = y + (random_hole(random_generator)/2u*2u+1u);

    /* Place the wall. */
    for (uint32_t i = y; i < (y+height-1u); i++)
    {
      area[i][new_wall] = wall;
    }
    /* Place the hole. */
    area[new_hole][new_wall] = hole;

    /* Calculate the new values for the next run. */
    new_height = height;
    new_width = new_wall-x+1u;
    /* Complementary pairs. 'The other side of the wall.' */
    y_pair = y;
    x_pair = new_wall;
    new_height_pair = height;
    new_width_pair = x+width-new_wall;
  }
  else
  {
    /* Do nothing. */
  }

  /* Call it again. */
  divide(y, x, new_height, new_width);
  /* When there are no more places left, then go to the 'other side'. */
  divide(y_pair, x_pair, new_height_pair, new_width_pair);
}

