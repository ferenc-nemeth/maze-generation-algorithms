/**
 * @file    file_system.h
 * @author  Ferenc Nemeth
 * @date    2 Jan 2019
 * @brief   Saves and loads the maze to/from the file system.
 *
 *          Copyright (c) 2019 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#ifndef FILE_SYSTEM_H_
#define FILE_SYSTEM_H_

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "maze_generator.h"

namespace maze
{
  class file_system
  {
    public:
      void save(std::vector<std::vector<uint32_t>> vect, std::string filename);
      std::vector<std::vector<uint32_t>> load(std::string filename);

    private:
      static constexpr uint32_t factor = 20u;
      const cv::Vec3b white = cv::Vec3b(255u, 255u, 255u);
      const cv::Vec3b black = cv::Vec3b(0u, 0u, 0u);
      const cv::Vec3b red   = cv::Vec3b(0u,0u,255u);
  };
}

#endif /* FILE_SYSTEM_H_ */

