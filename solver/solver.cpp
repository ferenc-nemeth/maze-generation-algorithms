/**
 * @file    solver.cpp
 * @author  Ferenc Nemeth
 * @date    8 Jan 2019
 * @brief   Solving algorithms for mazes.
 *
 *          Copyright (c) 2019 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "solver.h"

/**
 * @brief   Solves the maze with dead-end filling algorithm.
 *          This implementation only works if the entrance and exit are at the border of the maze. 
 *          The implementation and usage is easier this way, but it is possible to do it in the 'normal way'.
 * @param   &vect - The vector-vector of the maze we want to solve. It overwrites the input one.
 * @return  void
 */
void maze::solver::dead_end(std::vector<std::vector<uint32_t>> &vect)
{
  bool found_dead_end = true;

  /* Loop until there are dead-ends. */
  while(found_dead_end)
  { 
    found_dead_end = false;
    /* Loop through the maze. */
    for(uint32_t y = 1u; y < vect.size(); y += 2u)
    {
      for(uint32_t x = 1u; x < vect[y].size(); x += 2u)
      {
        uint32_t dead_end_counter = 4u;
        uint32_t possible_y = 0u;
        uint32_t possible_x = 0u;

        /* Check the 4 directions of the hole. */
        if (hole == vect[y-1u][x])
        {
          dead_end_counter--;
          possible_y = y-1u;
          possible_x = x;
        }

        if (hole == vect[y+1u][x])
        {
          dead_end_counter--;
          possible_y = y+1u;
          possible_x = x;
        }

        if (hole == vect[y][x-1u])
        {
          dead_end_counter--;
          possible_y = y;
          possible_x = x-1u;
        }

        if (hole == vect[y][x+1u])
        {
          dead_end_counter--;
          possible_y = y;
          possible_x = x+1u;
        }

        /* If a hole has 3 walls (or dead-ends) next to it, then it is a dead-end. */
        /* Mark that hole and the only hole next to it. */
        if (3u == dead_end_counter)
        {
          vect[y][x] = dead;
          vect[possible_y][possible_x] = dead;
          found_dead_end = true;
        }
      }
    }
  }

  /* Clean-up. Turn every hole into solution and turn back every dead-end into a hole. */
  for(uint32_t y = 0u; y < vect.size(); y++)
  {
    for(uint32_t x = 0u; x < vect[y].size(); x++)
    {
      if (hole == vect[y][x])
      {
        vect[y][x] = solution;
      }
      else if (dead == vect[y][x])
      {
        vect[y][x] = hole;
      }
      else
      {
        /* Do nothing. */
      }
    }
  }
}

/**
 * @brief   Solves the maze with wall follower algorithm.
 * @param   &vect       - The vector-vector of the maze we want to solve. It overwrites the input one.
 * @param   entrance_y  - Y coordinate of the entrance.
 * @param   entrance_x  - X coordinate of the entrance.
 * @param   exit_y      - Y coordinate of the exit.
 * @param   exit_x      - X coordinate of the exit.
 * @param   rule        - Which hand rule to use. Either left (0) or right (1). The defult value is left.
 * @return  void
 */
void maze::solver::wall_follower(std::vector<std::vector<uint32_t>> &vect, uint32_t entrance_y, uint32_t entrance_x, uint32_t exit_y, uint32_t exit_x, uint32_t rule)
{
  uint32_t y = entrance_y;
  uint32_t x = entrance_x;
  uint32_t direction = north;
  std::vector<uint32_t> directions(4);
  std::vector<element> visited;
  visited.push_back({y, x, 99u}); /* The first direction has to be invalid, so it never gets removed. */
  vect[y][x] = solution;

  /* Loop until, we aren't at the end. */
  while(!((y == exit_y) && (x == exit_x)))
  {

    /* Left-hand rule and its priorities. */
    if (left == rule)
    {
      if (north == direction)
      {
        directions = {west, north, east, south};
      }
      else if (south == direction)
      {
        directions = {east, south, west, north};
      }
      else if (west == direction)
      {
        directions = {south, west, north, east};
      }
      else if (east == direction)
      {
        directions = {north, east, south, west};
      }
      else
      {
        /* Do nothing. */
      }
    }
    /* Right-hand rule and its priorities. */
    else if (right == rule)
    {
      if (north == direction)
      {
        directions = {east, north, west, south};
      }
      else if (south == direction)
      {
        directions = {west, south, east, north};
      }
      else if (west == direction)
      {
        directions = {north, west, south, east};
      }
      else if (east == direction)
      {
        directions = {south, east, north, west};
      }
      else
      {
        /* Do nothing. */
      }
    }
    else
    {
      /* Do nothing. */
    }

    
    /* Try to move in every direction. */
    /* If it is possible to go there, then go. */
    /* If we haven't been there, then push it to the visited stack and mark as a solution. */
    /* If we have benn there, then pop it from the visited stack and remove the soliton mark. */
    for (uint32_t i = 0u; i < directions.size(); i++)
    {
      if (north == directions[i])
      {
        if ((y > 1u) && (wall != vect[y-1u][x]))
        {
          uint32_t last = visited.size()-1u;
          y--;
          direction = north;
          if (south == visited[last].direction)
          {
            vect[visited[last].y][visited[last].x] = hole;
            visited.pop_back();
          }
          else
          {
            visited.push_back({y, x, direction});
            vect[y][x] = solution;
          }
          break;
        }
      }
      else if (south == directions[i])
      {
        if (((y+1u) < vect.size()) && (wall != vect[y+1u][x]))
        {
          uint32_t last = visited.size()-1u;
          y++;
          direction = south;
          if (north == visited[last].direction)
          {
            vect[visited[last].y][visited[last].x] = hole;
            visited.pop_back();
          }
          else
          {
            visited.push_back({y, x, direction});
            vect[y][x] = solution;
          }
          break;
        }
      }
      else if (west == directions[i])
      {
        if ((x > 1u) && (wall != vect[y][x-1u]))
        {
          uint32_t last = visited.size()-1u;
          x--;
          direction = west;
          if (east == visited[last].direction)
          {
            vect[visited[last].y][visited[last].x] = hole;
            visited.pop_back();
          }
          else
          {
            visited.push_back({y, x, direction});
            vect[y][x] = solution;
          }
          break;
        }
      }
      else if (east == directions[i])
      {
        if (((x+1u) < vect[0u].size()) && (wall != vect[y][x+1u]))
        {
          uint32_t last = visited.size()-1u;
          x++;
          direction = east;
          if (west == visited[last].direction)
          {
            vect[visited[last].y][visited[last].x] = hole;
            visited.pop_back();
          }
          else
          {
            visited.push_back({y, x, direction});
            vect[y][x] = solution;
          }
          break;
        }
      }
      else
      {
        /* Do nothing. */
      }
    }
  }
}


