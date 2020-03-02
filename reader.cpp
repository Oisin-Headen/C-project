/******************************************************************************
 * Author Name: Paul Miller
 * Author ID: E70949
 * File Name: reader.cpp
 * All copyright in this material resides with RMIT University.
 *****************************************************************************/
/******************************************************************************
 * purpose of this file: contains implementations of the algorithms to read in
 * lines from a file with each of the data structures in this project
 *****************************************************************************/
#include "reader.h"

/* please note that each function in this module returns a unique_ptr only as
 * a check that the operation succeeded. I would have used std::optional but
 * it does not accept non-copyable classes.
 *
 * Also I have used the string_view class which is simply a thin wrapper around
 * a char pointer as is more efficient (both in time and space ) to pass around
 * than a std::string especially if we don't need to modify it. You should have
 * a read over its documentation.
 */

/**
 * load a file into a datastructure
 **/
std::unique_ptr<cpt323::datastructure::datastructure> 
    cpt323::reader::readfile(std::string_view filename, const std::string& datastructure_type)
{
    std::unique_ptr<cpt323::datastructure::datastructure> the_datastructure;

    /* open the file and check for errors */
    std::ifstream in(filename.data());
    if (!in)
    {
        perror("failed to open file for reading");
        return nullptr;
    }
    /* we should throw an io exception when the fail or bad bits are set
     * on the stream
     */
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Create the datastructrue based on what the user passed in.
        if(datastructure_type == "list")
        {
            the_datastructure = std::make_unique<cpt323::list::custom_list>();
        }
        else if (datastructure_type == "tree")
        {
            the_datastructure = std::make_unique<cpt323::tree::custom_tree>();
        }
        else if (datastructure_type == "stdlist")
        {
            the_datastructure = std::make_unique<cpt323::stdlist::stdlist_wrapper>();
        }
        else if (datastructure_type == "set")
        {
            the_datastructure = std::make_unique<cpt323::set::set_wrapper>();
        }
        else if (datastructure_type == "vector")
        {
            the_datastructure = std::make_unique<cpt323::vector::vector_wrapper>();
        }
        else
        {
            return nullptr;
        }
        
        /* read each line from the file */
        std::string line;
        while (std::getline(in, line))
        {
            the_datastructure->add(line);
        }
    }
    catch (std::bad_alloc& ba)
    {
        /* handle the memory allocation errors */
        perror("memory allocation error");
        return nullptr;
    }
    catch (std::ios::failure& iff)
    {
        /* check if we are at the end of the file and if we are not,
         * display an error appropriate to the io error that has occured
         */
        if (!in.eof())
        {
            perror("failed to read file");
            return nullptr;
        }
    }
    catch (std::exception& ex)
    {
        /* handle any other errors */
        std::cerr << ex.what() << "\n";
    }
    return the_datastructure;
}
