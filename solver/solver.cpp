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
 * @param   &vect - The vector-vector of the maze we want to solve. It overwrites the input one.
 * @param   entrance_y  - Y coordinate of the entrance.
 * @param   entrance_x  - X coordinate of the entrance.
 * @param   exit_y      - Y coordinate of the exit.
 * @param   exit_x      - X coordinate of the exit.
 * @return  void
 */
void maze::solver::dead_end(std::vector<std::vector<uint32_t>> &vect, uint32_t entrance_y, uint32_t entrance_x, uint32_t exit_y, uint32_t exit_x)
{
  error_check(vect, entrance_y, entrance_x, exit_y, exit_x);

  /* Separate the entrace and exit from everything. */
  vect[entrance_y][entrance_x] = never_dead;
  vect[exit_y][exit_x] = never_dead;
  bool found_dead_end = true;

  /* Loop until there are dead-ends. */
  while(found_dead_end)
  { 
    found_dead_end = false;
    /* Loop through the maze. */
    for(uint32_t y = 0u; y < vect.size(); y++)
    {
      for(uint32_t x = 0u; x < vect[y].size(); x++)
      {
        uint32_t dead_end_counter = 0u;

        if (hole == vect[y][x])
        {
          /* Check the 4 directions of the hole. */
          /* North. */
          if ((y > 0u) && ((wall == vect[y-1u][x]) || (dead == vect[y-1u][x])))
          {
            dead_end_counter++;
          }
          /* South. */
          if (((y+1u) < vect.size()) && ((wall == vect[y+1u][x]) || (dead == vect[y+1u][x])))
          {
            dead_end_counter++;
          }
          /* West. */
          if ((x > 0u) && ((wall == vect[y][x-1u]) || (dead == vect[y][x-1u])))
          {
            dead_end_counter++;
          }
          /* East. */
          if (((x+1u) < vect[0u].size()) && ((wall == vect[y][x+1u]) || (dead == vect[y][x+1u])))
          {
            dead_end_counter++;
          }

          /* If a hole has 3 walls (or dead-ends) next to it, then it is a dead-end. */
          /* The boundaries are dead-ends in every case. */
          if ((3u == dead_end_counter) \
          || ((0u == y) || (0u == x) || (vect.size()-1u == y) || (vect[0u].size()-1u == x)))
          {
            vect[y][x] = dead;
            found_dead_end = true;
          }
        }
      }
    }
  }

  /* Clean-up. Turn every hole (+ the separted entrance and exit) into a solution and turn back every dead-end into a hole. */
  for(uint32_t y = 0u; y < vect.size(); y++)
  {
    for(uint32_t x = 0u; x < vect[y].size(); x++)
    {
      if ((hole == vect[y][x]) || (never_dead == vect[y][x]))
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
 * @brief   Solves the maze with Dijstra's algorithm.
 * @param   &vect       - The vector-vector of the maze we want to solve. It overwrites the input one.
 * @param   entrance_y  - Y coordinate of the entrance.
 * @param   entrance_x  - X coordinate of the entrance.
 * @param   exit_y      - Y coordinate of the exit.
 * @param   exit_x      - X coordinate of the exit.
 * @return  void
 */
void maze::solver::dijkstra(std::vector<std::vector<uint32_t>> &vect, uint32_t entrance_y, uint32_t entrance_x, uint32_t exit_y, uint32_t exit_x)
{
  error_check(vect, entrance_y, entrance_x, exit_y, exit_x);

  std::vector<distance> distances;
  uint32_t distance_cnt = 3u; /* Should be 0, but 0-2 are already used, so it would confuse everything. */
  distances.push_back({entrance_y, entrance_x}); 
  bool new_distance = true;
  uint32_t y = 0u;
  uint32_t x = 0u;

  /* Walk away from the entrace and save their distance (from the entrance). */
  while(new_distance)
  {
    new_distance = false;
    uint32_t distance_max = distances.size();
    distance_cnt++;
    /* With the for loop, we can walk "parellel". */
    /* If there are 2 path, then there'll 2 elements in the vector, if there are 3, then 3, etc..*/
    for (uint32_t i = 0u; i < distance_max; i++)
    {
      y = distances[0u].y;
      x = distances[0u].x;

      vect[y][x] = distance_cnt;
      /* if north is a hole, then save. */
      if ((y > 0u) && (hole == vect[y-1u][x]))
      {
        distances.push_back({y-1u,x});
        new_distance = true;
      }
      /* Ff south is a hole, then save. */
      if (((y+1u) < vect.size()) && (hole == vect[y+1u][x]))
      {
        distances.push_back({y+1u,x});
        new_distance = true;
      }
      /* if west is a hole, then save. */
      if ((x > 0u) && (hole == vect[y][x-1u]))
      {
        distances.push_back({y,x-1u});
        new_distance = true;
      }
      /* If east is a hole, then save. */
      if (((x+1u) < vect[0u].size()) && (hole == vect[y][x+1u]))
      {
        distances.push_back({y,x+1u});
        new_distance = true;
      }
      
      /* Stop at the end. It could run and check every cell in the maze, but it would be waste of time. */
      if ((y == exit_y) && (x == exit_x))
      {
        new_distance = false;
        break;
      }

      distances.erase(distances.begin());
    }
  }

  /* Walk back from the exit to the entrance. */
  y = exit_y;
  x = exit_x;
  distance_cnt = vect[y][x];

  /* Loop until we aren't at the beginning. */
  while(3u != distance_cnt)
  {
    /* Mark everything as a solution on the way. */
    vect[y][x] = solution;
    distance_cnt--;
    if ((y > 0u) && (distance_cnt == vect[y-1u][x]))
    {
      y--;
    }
    else if (((y+1u) < vect.size()) && (distance_cnt == vect[y+1u][x]))
    {
      y++;
    }
    else if ((x > 0u) && (distance_cnt == vect[y][x-1u]))
    {
      x--;
    }
    else if (((x+1u) < vect[0u].size()) && (distance_cnt == vect[y][x+1u]))
    {
      x++;
    }
    else
    {
      /* Do nothing. */
    }
  }

  /* Clean up, the output shall only contain walls, holes or solutions. */
  for(uint32_t y = 0u; y < vect.size(); y++)
  {
    for(uint32_t x = 0u; x < vect[y].size(); x++)
    {
      if ((wall != vect[y][x]) && (solution != vect[y][x]))
      {
        vect[y][x] = hole;
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
  error_check(vect, entrance_y, entrance_x, exit_y, exit_x);

  uint32_t y = entrance_y;
  uint32_t x = entrance_x;
  uint32_t direction = north;
  std::vector<uint32_t> directions(4);
  std::vector<element> visited;
  visited.push_back({y, x, 99u}); /* The first direction has to be invalid, so it never gets removed. */
  vect[y][x] = solution;

  /* Loop until we aren't at the end. */
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
    /* If it is possible to go there, then go (the directions are in priority order). */
    /* If we haven't been there, then push it to the visited stack and mark as a solution. */
    /* If we have been there, then pop it from the visited stack and remove the soliton mark. */
    for (uint32_t i = 0u; i < directions.size(); i++)
    {
      if (north == directions[i])
      {
        if ((y > 0u) && (wall != vect[y-1u][x]))
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
        if ((x > 0u) && (wall != vect[y][x-1u]))
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

/**
 * @brief   Error handler for the solver algorithms. It shall be insterted into every member function.
 * @param   &vect       - The vector-vector of the maze we want to solve. It overwrites the input one.
 * @param   entrance_y  - Y coordinate of the entrance.
 * @param   entrance_x  - X coordinate of the entrance.
 * @param   exit_y      - Y coordinate of the exit.
 * @param   exit_x      - X coordinate of the exit.
 * @return  void
 */
void maze::solver::error_check(std::vector<std::vector<uint32_t>> vect, uint32_t entrance_y, uint32_t entrance_x, uint32_t exit_y, uint32_t exit_x)
{
  if ((vect.size() <= entrance_y) || (vect[0u].size() <= entrance_x) || (vect.size() <= exit_y) || (vect[0u].size() <= exit_x))
  {
    throw std::invalid_argument("Out of boundary!");
  }

  if ((hole != vect[entrance_y][entrance_x]) || (hole != vect[entrance_y][entrance_x]))
  {
    throw std::invalid_argument("The entrance and exit must be holes (0).");
  }
}

