/**
 * @file    binary_tree.h
 * @author  Ferenc Nemeth
 * @date    18 Nov 2018
 * @brief   Maze generator class with binary tree algorithm.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include "maze_generator.h"

namespace maze
{
  class binary_tree: public maze_generator
  {
    public:
      using maze_generator::maze_generator;
      void generate(void);
    
    private:      
      static constexpr uint32_t none = 2u; /**< Third option after vertical and horizontal. */
  };
}

#endif /* BINARY_TREE_H_ */

