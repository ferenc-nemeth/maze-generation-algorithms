/**
 * @file    save.h
 * @author  Ferenc Nemeth
 * @date    3 Dec 2018
 * @brief   Saves the input vector.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#ifndef SAVE_H_
#define SAVE_H_

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

void save_to_file(std::vector<std::vector<uint32_t>> vect, std::string filename);

#endif /* SAVE_H_ */

