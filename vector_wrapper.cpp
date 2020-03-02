#include "vector_wrapper.h"


// vector_wrapper methods

// Add an item to the vector.
void cpt323::vector::vector_wrapper::add(const std::string& new_line)
{
    inner_vector.push_back(new_line);
}

// Get an iterator to the begining of the vector.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::vector::vector_wrapper::begin()
{
    auto begin_iter = std::make_unique<vector_iterator>(inner_vector.begin());
    return begin_iter;
}

// Get an iterator to the end of the vector
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::vector::vector_wrapper::end()
{
    auto end_iter = std::make_unique<vector_iterator>(inner_vector.end());
    return end_iter;
}

// Get the size of the vector
std::size_t cpt323::vector::vector_wrapper::size()
{
    return inner_vector.size();
}

// Sort the vector
void cpt323::vector::vector_wrapper::sort()
{
    std::sort(inner_vector.begin(), inner_vector.end());
}

// Is the vector empty?
bool cpt323::vector::vector_wrapper::empty()
{
    return inner_vector.empty();
}


// vector_iterator methods

// Get the data from the iterator.
const std::string& cpt323::vector::vector_wrapper::vector_iterator::operator*(void) const 
{
    return inner.operator*();
}

// Pre-increment operator
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::vector::vector_wrapper::vector_iterator::operator++(void) 
{
    return std::make_unique<vector_iterator>(++inner);
}

// Post-increment operator
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::vector::vector_wrapper::vector_iterator::operator++(int) 
{
    auto new_iter = std::make_unique<vector_iterator>(inner);
    ++inner;
    return new_iter;
}

// Are these two iterators equal?
bool cpt323::vector::vector_wrapper::vector_iterator::operator==(
    const cpt323::datastructure::datastructure::iterator& iter) 
{
    auto cast_iter = dynamic_cast<const vector_iterator *>(&iter);
    // If the iterators are of different types, they're not equal
    if(cast_iter == nullptr)
    {
        return false;
    }
    return cast_iter->inner == inner;
}

// Are these two iterators not equal?
bool cpt323::vector::vector_wrapper::vector_iterator::operator!=(
    const cpt323::datastructure::datastructure::iterator& iter) 
{
    return !(*this == iter);
}