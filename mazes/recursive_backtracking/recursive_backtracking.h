/**
 * @file    recursive_backtracking.h
 * @author  Ferenc Nemeth
 * @date    18 Nov 2018
 * @brief   Maze generator class with recursive backtracking algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#ifndef RECURSIVE_BACKTRACKING_H_
#define RECURSIVE_BACKTRACKING_H_

#include "maze_generator.h"

namespace maze
{
  class recursive_backtracking: public maze_generator
  {
    public:
      using maze_generator::maze_generator;
      void generate(void);

    private:
      void crave_passage(uint32_t y, uint32_t x);
  };
}

#endif /* RECURSIVE_BACKTRACKING_H_ */

