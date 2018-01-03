/*
 * tools.h
 *
 *  Created on: Nov 7, 2017
 *      Author: shado
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <crtdefs.h>
#include <tuple>
#include <cstring>
#include <iostream>
#include <vector>

#include "log.h"//Basic logging

//Big-endian to little endian conversion function
template <typename T> T reverse(T t);

//Memory helper function
template <typename T> T get(char* p, bool bigEndian);

//basic string search
extern bool contains(const char* str, const char* key);

extern bool fileExists(const char* filename);

template <typename T> void convert(std::string s, T& out);

#include "tools-imp.h"

#endif /* TOOLS_H_ */
