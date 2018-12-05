/**
 * @file    kruskal.cpp
 * @author  Ferenc Nemeth
 * @date    23 Nov 2018
 * @brief   Maze generator class with Kruskal's algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "kruskal.h"

/**
 * @brief   This method generates the maze with Kruskal's algorithm.
 * @param   void
 * @return  void
 */
void maze::kruskal::generate(void)
{
  /* Mersenne Twister 19937 pseudo-random generator. */
  std::mt19937 random_generator(random_device());

  /* Do the initialization for sets, similar way to area. */
  sets.resize(area.size());
  for (uint32_t y = 0u; y < area.size(); y++)
  {
    sets[y].resize(area[y].size());
  }

  /* Save every y,x coordinate with a possible movement (vertical or horizontal). */
  /* Also, fill the sets with different values. */  
  std::vector<element> elements;
  uint32_t i = 1u;
  for (uint32_t y = 1u; y < (sets.size()-1u); y+=2u)
  {
    for (uint32_t x = 1u; x < (sets[0u].size()-1u); x+=2u)
    {
      if ((y+2u) < (sets.size()-1u))
      {
        elements.push_back({y, x, vertical});
      }
      if ((x+2u) < (sets[0u].size()-1u))
      {
        elements.push_back({y, x, horizontal});
      }
      sets[y][x] = i;
      i++;
    }
  }

  /* Shuffle the elements vector. */
  std::shuffle(elements.begin(), elements.end(), random_generator);

  /* Do it until there are no elements left. */
  while(elements.size())
  {
    uint32_t y = elements[elements.size()-1u].y;
    uint32_t x = elements[elements.size()-1u].x;
    uint32_t orientation = elements[elements.size()-1u].orientation;
    elements.pop_back();    

    if (horizontal == orientation)
    {
      /* If the two sets are different, then make them the same and crave a passage. */
      if (sets[y][x+2u] != sets[y][x])
      {
        replace(sets[y][x+2u], sets[y][x]);
        for (uint32_t j = 0u; j < 3u; j++)
        {
          area[y][x+j] = hole;
        }
      }
    }
    else if (vertical == orientation)
    {
      /* If the two sets are different, then make them the same and crave a passage. */
      if (sets[y+2u][x] != sets[y][x])
      {
        replace(sets[y+2u][x], sets[y][x]);
        for (uint32_t j = 0u; j < 3u; j++)
        {
          area[y+j][x] = hole;
        }
      }
    }
    else
    {
      /* Do nothing. */
    }
  }
}

/**
 * @brief   Loops through the sets array and replaces the chosen elements.
 * @param   set_to replace - The type of set, that needs to replaced.
 * @param   sample_set     - The new value, that's going to overwrite the others.
 * @return  void
 */
void maze::kruskal::replace(uint32_t set_to_replace, uint32_t sample_set)
{
  for (uint32_t search_y = 1u; search_y < (sets.size()-1u); search_y+=2u)
  {
    for (uint32_t search_x = 1u; search_x < (sets[0u].size()-1u); search_x+=2u)
    {
      if (sets[search_y][search_x] == set_to_replace)
      {
        sets[search_y][search_x] = sample_set;
      }
    }
  }
}

