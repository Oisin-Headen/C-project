/******************************************************************************
 * Author Name: Paul Miller
 * Author ID: E70949
 * File Name: saver.cpp
 * All copyright in this material resides with RMIT University.
 *****************************************************************************/
/******************************************************************************
 * purpose of this file: implements the functions to save to a file the contests
 * of a data structure in the order the elements are currently stored.
 *****************************************************************************/
#include "saver.h"

/**
 * save a datastructure to a text file
 **/
bool cpt323::saver::saver::savefile(std::string& filename,
                    std::vector<std::unique_ptr<cpt323::datastructure::datastructure>>& datastructures)
{
    // A vector of pairs of iterators.
    std::vector<std::pair<std::unique_ptr<datastructure::datastructure::iterator>, 
        std::unique_ptr<datastructure::datastructure::iterator>>> iterator_pairs;

    // For each datastructure, create an iterator for the begining and end, and save them as a pair.
    for (auto& datastructure : datastructures)
    {
        iterator_pairs.push_back(std::pair<std::unique_ptr<datastructure::datastructure::iterator>, 
            std::unique_ptr<datastructure::datastructure::iterator>>(
            datastructure->begin(), datastructure->end()));
    }

    /* open the file for output */
    std::ofstream out(filename.data());
    if (!out)
    {
        perror("failed to open file for saving");
        return false;
    }
    /* specify the io exceptions to throw */
    out.exceptions(std::ios::failbit | std::ios::badbit);
    try
    {
        // The datastructures are written out in sorted order. 
        // This assumes all datastructures have been sorted already.
        bool done = false;
        while(!done)
        {
            // Pointer to the lowest iterator.
            cpt323::datastructure::datastructure::iterator* lowest_iter = nullptr;
            // If there are no iterators left, the loop ends.
            done = true;
            // For each iterator,
            for (auto &iterator : iterator_pairs)
            {
                // Check if the iterator is finished.
                if(*iterator.first == *iterator.second)
                {
                    // This iterator has reached the end, do nothing.   
                }
                // Otherwise, if there is no current lowest iterator,
                // set this one as the lowest.
                else if(lowest_iter == nullptr)
                {   
                    lowest_iter = iterator.first.get();
                }
                // Otherwise, if this iterator is lower than the current lowest iterator, 
                // set this one as the new lowest
                else if(**lowest_iter > **iterator.first)
                {
                    lowest_iter = iterator.first.get();
                }
            }
            // If there is a lowest iterator,
            if(lowest_iter != nullptr)
            {
                // The loop is not yet finished.
                done = false;
                // Write out the line.
                out << **lowest_iter << '\n';
                // Increment the current lowest iterator.
                ++*lowest_iter;
            }
        }
    }
    catch (std::ios::failure& iff)
    {
        /* handle any errors in writing */
        perror("failed to save the file");
        return false;
    }
    return true;
}
