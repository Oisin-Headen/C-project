#include <memory>
#include "datastructure.h"

namespace cpt323::datastructure
{   
    // These free functions allow a range based for loop to work.
    std::unique_ptr<cpt323::datastructure::datastructure::iterator> 
        operator++(std::unique_ptr<cpt323::datastructure::datastructure::iterator>& iter);
    bool operator!=(const std::unique_ptr<cpt323::datastructure::datastructure::iterator>&, 
        const std::unique_ptr<cpt323::datastructure::datastructure::iterator>&);
}