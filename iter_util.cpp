#include "iter_util.h"

// How to increment a unique_ptr to an iterator.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> 
    cpt323::datastructure::operator++(std::unique_ptr<cpt323::datastructure::datastructure::iterator>& iter)
{
    return ++*iter;
}

// How to compare unique_ptrs to iterators with !=.
bool cpt323::datastructure::operator!=(const std::unique_ptr<cpt323::datastructure::datastructure::iterator>& iter, 
    const std::unique_ptr<cpt323::datastructure::datastructure::iterator>& otheriter)
{
    return iter->operator!=(*otheriter);
}