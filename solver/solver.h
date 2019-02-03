/**
 * @file    solver.h
 * @author  Ferenc Nemeth
 * @date    8 Jan 2019
 * @brief   Solving algorithms for mazes.
 *
 *          Copyright (c) 2019 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#ifndef SOLVER_H_
#define SOLVER_H_

#include <vector>
#include <random>
#include <algorithm>
#include "maze_generator.h"

namespace maze
{
  class solver
  {
    public:
      void dead_end(std::vector<std::vector<uint32_t>> &vect, uint32_t entrance_y, uint32_t entrance_x, uint32_t exit_y, uint32_t exit_x);
      void dijkstra(std::vector<std::vector<uint32_t>> &vect, uint32_t entrance_y, uint32_t entrance_x, uint32_t exit_y, uint32_t exit_x);
      void wall_follower(std::vector<std::vector<uint32_t>> &vect, uint32_t entrance_y, uint32_t entrance_x, uint32_t exit_y, uint32_t exit_x, uint32_t rule = left);

      static constexpr uint32_t left  = 0u;
      static constexpr uint32_t right = 1u;

    private:
      static constexpr uint32_t wall        = maze_generator::wall;
      static constexpr uint32_t hole        = maze_generator::hole;
      static constexpr uint32_t solution    = maze_generator::solution;
      static constexpr uint32_t dead        = 3u;
      static constexpr uint32_t never_dead  = 4u;

      static constexpr uint8_t north  = 0u;
      static constexpr uint8_t south  = 1u;
      static constexpr uint8_t west   = 2u;
      static constexpr uint8_t east   = 3u;

      /* For wall follower algorithm. */
      struct element {
        uint32_t y;
        uint32_t x;
        uint32_t direction;
      };

      /* For Dijkstra's algorithm. */
      struct distance {
        uint32_t y;
        uint32_t x;
      };

      void error_check(std::vector<std::vector<uint32_t>> vect, uint32_t entrance_y, uint32_t entrance_x, uint32_t exit_y, uint32_t exit_x);

  };
}

#endif /* SOLVER_H_ */

