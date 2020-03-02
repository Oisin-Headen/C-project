/******************************************************************************
 * Author Name: Paul Miller
 * Author ID: E70949
 * File Name: reader.h
 * All copyright in this material resides with RMIT University.
 *****************************************************************************/
/******************************************************************************
 * purpose of this file: specifies the prototype for the functions to read
 * from a text file into each data structure.
 *****************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <string_view>
#include "list.h"
#include "tree.h"
#include "stdlist_wrapper.h"
#include "set_wrapper.h"
#include "vector_wrapper.h"

#pragma once


namespace cpt323::reader
{
    std::unique_ptr<cpt323::datastructure::datastructure> readfile(std::string_view, const std::string&);
} // namespace cpt323::reader
