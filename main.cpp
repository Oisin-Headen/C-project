/******************************************************************************
 * Author Name: Paul Miller
 * Author ID: E70949
 * File Name: main.cpp
 * All copyright in this material resides with RMIT University.
 *****************************************************************************/
/******************************************************************************
 * purpose of this file: contains the main() function for this application. it
 * validates command line arguments and if accepted, intialises data structures,
 * calls the sort function and then calls the function that writes data out to a
 * file.
 *****************************************************************************/
#include "main.h"

int main(int argc, char* argv[])
{
    /* filename used in this program */
    std::string outname;
    // Datastructure type
    std::string datastructure_type;

    /* create the options description for the program_options boost library
     */
    boost::program_options::options_description desc("options");
    desc.add_options()("help,h", "print help messages")
    	/* specify -o which is a required argument for specifying the file
    	   to
    	   output the sorted list of words to */
    	("output,o",
    	 boost::program_options::value<std::string>(&outname)->required(),
    	 "The file to output the sorted data into")
        ("datastructure,d",
         boost::program_options::value<std::string>(&datastructure_type)->required(),
         "The type of datastructure to use");

    /* the variables map filled out by processing the command line
     * argumemnts
     */
    boost::program_options::variables_map vm;
    try
    {
        /* store the results of processing the command line in the
         * variables map
         */
        auto options = boost::program_options::command_line_parser(argc, argv)
            .options(desc)
            .allow_unregistered()
            .run();
        boost::program_options::store(options, vm);

        /* if the user requested help, display help information */
        if (vm.count("help") > 0)
        {
            display_usage(argv[0]);
            std::cout << "help text here\n";
            return EXIT_SUCCESS;
        }

        std::vector<std::string> filenames = boost::program_options::collect_unrecognized(
            options.options, boost::program_options::collect_unrecognized_mode::include_positional);
        
        /* parsing is done so the boost library can validate that the
         * arguments
         * passed in are correct */
        boost::program_options::notify(vm);

        // A vector of the datastructures
        std::vector<std::unique_ptr<cpt323::datastructure::datastructure>> datastructures;

        // Time the reading function.
        auto read_begin = std::chrono::high_resolution_clock::now();

        // sort the files and load the iterators
        for (auto file : filenames)
        {
            // Read the file
            auto datastructure = cpt323::reader::readfile(file, datastructure_type);
            
            if(datastructure == nullptr)
            {
                /* if the file failed to load, or the datastructure type is invalid,
                 * send the failure value back to the operating system
                 */
                return EXIT_FAILURE;
            }
            // Add the datastructure to the vector
            datastructures.push_back(std::move(datastructure));
        }

        auto read_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> read_time = read_end - read_begin;
        // The use of std::endl is intentional, as endl flushes the buffer,
        // allowing the user to see what the program is up to.
        std::cout << "Read Time: " << (read_time.count() * 1000) << std::endl;


        // Time the sorting function.
        auto sort_begin = std::chrono::high_resolution_clock::now();
        for(auto& datastructure : datastructures)
        {
            // sorts each datastructure.
            datastructure->sort();
        }
        auto sort_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> sort_time = sort_end - sort_begin;
        // The use of std::endl is intentional, as endl flushes the buffer,
        // allowing the user to see what the program is up to.
        std::cout << "Sort Time: " << (sort_time.count() * 1000) << std::endl;


        
        // Time the saving function.
        auto save_begin = std::chrono::high_resolution_clock::now();
        // Save the files.
        cpt323::saver::saver::savefile(outname, datastructures);
        auto save_end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> save_time = save_end - save_begin;
        // The use of std::endl is intentional, as endl flushes the buffer,
        // allowing the user to see what the program is up to.
        std::cout << "Save Time: " << (save_time.count() * 1000) << std::endl;

        // Also outputs total time, i.e. the time between starting to read data and the end of writing data.
        std::chrono::duration<float> total_time = save_end - read_begin;
        std::cout << "Total Time: " << (total_time.count() * 1000) << std::endl;
    }
    catch (std::exception& ex)
    {
        /* handle any errors in loading of the file or processing the
         * data
         * structure */
        std::cerr << ex.what() << "\n";
        display_usage(argv[0]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * If the user entered the wrong arguments, this function is called. It simply
 * explains how to correctly use the program
 **/
void display_usage(std::string_view view)
{
    std::cout << "You should call this program in the following way: \n\t"
          << view << " [args]\n";
    std::cout
    	<< "\n\tWhere [args] must include the following options: \n\n";
    std::cout
    	<< "any number of files to merge sort.\n";
    std::cout
    	<< "-o followed by a filename path: the filename of the file to "
    	   "output data into.\n";
    std::cout
    	<< "-d followed by one of 'list', 'tree', 'stdlist', 'set', 'vector'"
           ", which determines the datastructure to use.\n";
}
