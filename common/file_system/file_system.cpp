/**
 * @file    file_system.cpp
 * @author  Ferenc Nemeth
 * @date    2 Jan 2019
 * @brief   Saves and loads the maze to/from the file system.
 *
 *          Copyright (c) 2019 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "file_system.h"

/**
 * @brief   Resizes (20 times bigger) and then saves the input vector-vector as an image.
 * @param   vect      - 2D vector.
 * @param   filename  - The filename and location.
 * @return  void
 */
void maze::file_system::save(std::vector<std::vector<uint32_t>> vect, std::string filename)
{
  /* Create a Mat with the same values as the input vector-vector. */
  cv::Mat mat_vect(vect.size(), vect[0u].size(), CV_8UC3);
  for(int32_t y = 0; y < mat_vect.rows; y++)
  { 
    for(int32_t x = 0; x < mat_vect.cols; x++)
    {
      if (maze::maze_generator::wall == vect[y][x])
      {
        mat_vect.at<cv::Vec3b>(y, x) = black;
      }
      else if (maze::maze_generator::hole == vect[y][x])
      {
        mat_vect.at<cv::Vec3b>(y, x) = white;
      }
      else
      {
        mat_vect.at<cv::Vec3b>(y, x) = red;
      }
    }
  }
  /* Create a bigger one. */
  cv::Mat mat_vect_bigger(vect.size()*factor, vect[0u].size()*factor, CV_8UC3);
  /* Resize the original. */
	cv::resize(mat_vect, mat_vect_bigger, cv::Size(), factor, factor, cv::INTER_NEAREST);
  /* Save. */
  imwrite(filename, mat_vect_bigger);
}

/**
 * @brief   Loads an image, resizes it (20 times smaller) and then returns it as a vector-vector.
 * @param   filename  - The filename and location.
 * @return  vect      - vector-vector of the input image.
 */
std::vector<std::vector<uint32_t>> maze::file_system::load(std::string filename)
{
  /* Load. */
  cv::Mat mat_vect = cv::imread(filename, cv::IMREAD_COLOR);
  /* Create a smaller one. */
  cv::Mat mat_vect_smaller(cv::Size(mat_vect.cols/factor, mat_vect.rows/factor), CV_8UC3);
  std::vector<std::vector<uint32_t>> vect;
  /* Resize the original. */
	cv::resize(mat_vect, mat_vect_smaller, cv::Size(mat_vect.cols/factor, mat_vect.rows/factor), cv::INTER_NEAREST);

  /* Convert it a vector-vector. */
  vect.resize(mat_vect_smaller.rows);
  for(int32_t y = 0; y < mat_vect_smaller.rows; y++)
  { 
    vect[y].resize(mat_vect_smaller.cols);
    for(int32_t x = 0; x < mat_vect_smaller.cols; x++)
    {
      if (black == mat_vect_smaller.at<cv::Vec3b>(y, x))
      {
        vect[y][x] = maze::maze_generator::wall;
      }
      else if (white == mat_vect_smaller.at<cv::Vec3b>(y, x))
      {
        vect[y][x] = maze::maze_generator::hole;
      }
    }
  }

  return vect;
}

