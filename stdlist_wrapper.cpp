#include "stdlist_wrapper.h"

// stdlist_wrapper methods

// Add an item to the list.
void cpt323::stdlist::stdlist_wrapper::add(const std::string& line)
{
    inner.push_back(line);
}

// Create an iterator to the begining of the list.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::stdlist::stdlist_wrapper::begin()
{
    auto begin_iter = std::make_unique<stdlist_iterator>(inner.begin());
    return begin_iter;
}

// Creates an iterator for the end of the list.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::stdlist::stdlist_wrapper::end()
{
    auto end_iter = std::make_unique<stdlist_iterator>(inner.end());
    return end_iter;
}

// Gets the size of the list.
std::size_t cpt323::stdlist::stdlist_wrapper::size()
{
    return inner.size();
}

// Sorts the list.
void cpt323::stdlist::stdlist_wrapper::sort()
{
    inner.sort();
}

// Is the list empty?
bool cpt323::stdlist::stdlist_wrapper::empty()
{
    return inner.empty();
}

// set_iterator methods

// Get the value from the iterator.
const std::string& cpt323::stdlist::stdlist_wrapper::stdlist_iterator::operator*(void) const 
{
    return inner.operator*();
}

// Pre-increment Operator
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::stdlist::stdlist_wrapper::stdlist_iterator::operator++(void) 
{
    // Increment the iterator, and return a copy.
    return std::make_unique<stdlist_iterator>(++inner);
}

// Post-increment Operator.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::stdlist::stdlist_wrapper::stdlist_iterator::operator++(int) 
{
    // Make a copy, increment the inner iterator, and return the copy.
    auto new_iter = std::make_unique<stdlist_iterator>(inner);
    ++inner;
    return new_iter;
}

// Are these two iterators equal?
bool cpt323::stdlist::stdlist_wrapper::stdlist_iterator::operator==(
    const cpt323::datastructure::datastructure::iterator& iter) 
{
    // Cast the other iterator to a list_iterator and compare them.
    auto cast_iter = dynamic_cast<const stdlist_iterator *>(&iter);
    // If these are two different types of iterator, they aren't equal.
    if(cast_iter == nullptr)
    {
        return false;
    }
    return cast_iter->inner == inner;
}

// Are these two iterators not equal?
bool cpt323::stdlist::stdlist_wrapper::stdlist_iterator::operator!=(
    const cpt323::datastructure::datastructure::iterator& iter) 
{
    return !(*this == iter);
}