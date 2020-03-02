/******************************************************************************
 * Author Name: Paul Miller
 * Author ID: E70949
 * File Name: saver.h
 * All copyright in this material resides with RMIT University.
 *****************************************************************************/
/*******************************************************************************
 * purpose of this file: specifies the function prototypes for the functions to
 * save the data structure to a file specified by the string_view parameter.
 ******************************************************************************/
#include <fstream>
#include <iostream>
#include <list>
#include <string_view>
#include <set>
#include <vector>
#include <utility>
#include "list.h"
#include "tree.h"
// #include <memory>
#pragma once


namespace cpt323::saver
{
    class saver
    {
        public:
        static bool savefile(
            std::string&, std::vector<std::unique_ptr<cpt323::datastructure::datastructure>>&);
    };
} // namespace cpt323::saver
