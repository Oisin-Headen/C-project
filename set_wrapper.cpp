#include "set_wrapper.h"

// set_wrapper methods

// Add an item to the set.
void cpt323::set::set_wrapper::add(const std::string& line)
{
    inner_set.insert(line);
}

// Get an iterator to the begining of the set.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::set::set_wrapper::begin()
{
    // Return a new set_iterator wrapping an iterator to the begining of the inner set.
    auto begin_iter = std::make_unique<set_iterator>(inner_set.begin());
    return begin_iter;
}

// Get an iterator to the end of the set.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::set::set_wrapper::end()
{
    // Return a new set_iterator wrapping an iterator to the end of the inner set.
    auto end_iter = std::make_unique<set_iterator>(inner_set.end());
    return end_iter;
}

// Get the size of the set.
std::size_t cpt323::set::set_wrapper::size()
{
    return inner_set.size();
}

// Empty method, sets are already sorted.
void cpt323::set::set_wrapper::sort()
{
}

// Is this set empty?
bool cpt323::set::set_wrapper::empty()
{
    return inner_set.empty();
}

// set_iterator methods

// Get the value from the iterator.
const std::string& cpt323::set::set_wrapper::set_iterator::operator*(void) const 
{
    return inner.operator*();
}

// Pre-increment operator.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::set::set_wrapper::set_iterator::operator++(void) 
{
    // Increment the inner iterator, then return a copy set_iterator.
    return std::make_unique<set_iterator>(++inner);
}

// Post-increment operator.
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::set::set_wrapper::set_iterator::operator++(int) 
{
    // Create a copy set_iterator before incrementing.
    auto new_iter = std::make_unique<set_iterator>(inner);
    ++inner;
    // return the copy
    return new_iter;
}

// Does this iterator equal another iterator?
bool cpt323::set::set_wrapper::set_iterator::operator==(
    const cpt323::datastructure::datastructure::iterator& iter) 
{
    // Cast the other iterator to a set_iterator, then compare their inner iterators.
    auto cast_other = dynamic_cast<const set_iterator *>(&iter);
    // If these aren't the same type of iterator, they aren't equal.
    if (cast_other == nullptr)
    {
        return false;
    }
    return cast_other->inner == inner;
}

// Does this iterator not equal another iterator?
bool cpt323::set::set_wrapper::set_iterator::operator!=(
    const cpt323::datastructure::datastructure::iterator& iter) 
{
    return !(*this == iter);
}