/**
 * @file    save.cpp
 * @author  Ferenc Nemeth
 * @date    3 Dec 2018
 * @brief   Saves the input vector.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "save.h"

/**
 * @brief   Resizes (20 times bigger) and then saves the input vector-vector as an image (.png).
 * @param   vect      - 2D vector.
 * @param   filename  - The filename and location. Don't have to specify filename extension.
 * @return  void
 */
void save_to_file(std::vector<std::vector<uint32_t>> vect, std::string filename)
{
  constexpr uint32_t factor       = 20u;  /**< The output image is going to be *factor* times bigger. */
  constexpr uint32_t adjust_color = 255u; /**< 255: white; 0: black */
  filename += ".png";

  /* Create a Mat with the same values as the input vector-vecotor. */
  cv::Mat mat_vect(vect.size(), vect[0u].size(), CV_8UC1);
  for(int32_t y = 0; y < mat_vect.rows; y++)
  { 
    for(int32_t x = 0; x < mat_vect.cols; x++)
    {
      mat_vect.at<uint8_t>(y, x) = vect[y][x]*adjust_color;
    }
  }
  /* Create a bigger one. */
  cv::Mat mat_vect_bigger(vect.size()*factor, vect[0u].size()*factor, CV_8UC1);
  /* Resize the original. */
	cv::resize(mat_vect, mat_vect_bigger, cv::Size(), factor, factor, cv::INTER_NEAREST);
  /* Save. */
  imwrite(filename, mat_vect_bigger);
}

