/**
 * @file    prim.h
 * @author  Ferenc Nemeth
 * @date    19 Nov 2018
 * @brief   Maze generator class with Prim's algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#ifndef PRIM_H_
#define PRIM_H_

#include "maze_generator.h"

namespace maze
{
  class prim: public maze_generator
  {
    public:
      using maze_generator::maze_generator;
      void generate(void);

    private:      
      static constexpr uint32_t frontier = 2u; /**< Third option after wall and hole. */

      struct frontier_location {
              uint32_t y;
              uint32_t x;
      };

      std::vector<frontier_location> frontiers;

      void mark(uint32_t y, uint32_t x);
  };
}

#endif /* PRIM_H_ */

