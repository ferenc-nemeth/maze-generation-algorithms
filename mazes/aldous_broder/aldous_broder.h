/**
 * @file    aldous_broder.h
 * @author  Ferenc Nemeth
 * @date    20 Nov 2018
 * @brief   Maze generator class with Aldous-Broder algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#ifndef ALDOUS_BRODER_H_
#define ALDOUS_BRODER_H_

#include "maze_generator.h"

namespace maze
{
  class aldous_broder: public maze_generator
  {
    public:
      using maze_generator::maze_generator;
      void generate(void);
  };
}

#endif /* ALDOUS_BRODER_H_ */

