/******************************************************************************
 * Author Name: Paul Miller
 * Author ID: E70949
 * File Name: list.cpp
 * All copyright in this material resides with RMIT University.
 *****************************************************************************/
/******************************************************************************
 * purpose of this file: to provide the implementation of the custom list
 * class for this project.
 *****************************************************************************/
#include "list.h"

/**
 * the set_next() method of the of the node class. This method takes ownership
 * of the unique_ptr to node and moves it into the next pointer for this object.
 **/
void cpt323::list::list_node::set_next(std::unique_ptr<list_node>&& newnext)
{
    next = std::move(newnext);
}

/**
 * default constructor for the list class. Sets the list to be empty via setting
 * the head pointer to NULL and the count to 0.
 **/
cpt323::list::custom_list::custom_list(void) : head(nullptr), tail(nullptr), num_elts(0)
{
}

/**
 * add function - adds a string to the list of words that have been loaded in.
 **/
void cpt323::list::custom_list::add(const std::string& newstr)
{
    // Oisín Note: This line was causing issues when loading multiple files, 
    // changed the tail pointer to a member variable
    // static list_node* tail = nullptr;

    /* if we have been here before, just add to the end of the list */
    if (tail)
    {
        tail->set_next(std::make_unique<list_node>(newstr));
        /* make sure we keep the pointer to the tail updated for the
         * next insert
         */
        tail = tail->next.get();
    }
    else
    {
        /* otherwise, create a new node at the head */
        head = std::make_unique<list_node>(newstr);
        tail = head.get();
    }
    /* don't forget to increment the count of elements */
    ++num_elts;
}

/**
 * Constructor for an iterator - we point it at a node so we can start
 * iterating from there.
 **/
cpt323::list::custom_list::list_iterator::list_iterator(cpt323::list::list_node* anode) : inner(anode)
{
}

/**
 * gets the current size of the list
 **/
std::size_t cpt323::list::custom_list::size(void)
{
    return num_elts;
}

/**
 * the list's begin function which is required to return an iterator pointing
 * at the start of the list
 **/
std::unique_ptr<cpt323::datastructure::datastructure::iterator>  cpt323::list::custom_list::begin(void)
{
    return std::make_unique<list_iterator>(head.get());
}

/**
 * the list's end function which is required to return an iterator pointing
 * one element beyond the end of the list
 **/
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::list::custom_list::end(void)
{
    return std::make_unique<list_iterator>(nullptr);
}

/**
 * operator function that defines how to dereference an operator
 **/
const std::string& cpt323::list::custom_list::list_iterator::operator*(void) const
{
    return inner->data;
}

/**
 * increment operator for iterator - just points along to the next element.
 **/
std::unique_ptr<cpt323::datastructure::datastructure::iterator>  cpt323::list::custom_list::list_iterator::operator++(void)
{
    inner = inner->next.get();
    return std::make_unique<list_iterator>(inner);
}

/**
 * post increment operator for the list iterator - just capture the current
 * state, call the pre-increment operator then return the previous object.
 **/
std::unique_ptr<cpt323::datastructure::datastructure::iterator> cpt323::list::custom_list::list_iterator::operator++(int)
{
    list_iterator it = *this;
    operator++();
    return std::make_unique<list_iterator>(it);
}

/**
 * find_min() gives us a pair of pointers to unique_ptr<node>, one that points
 * at the previous node (the first) and one that points at the next pointer
 * (the second).
 **/
cpt323::list::nodeptrpair cpt323::list::custom_list::find_min(void)
{
    nodeptrpair pair(nullptr, nullptr);
    nodeptr current = &head, prev = nullptr;
    /* search for the minimum string (the string earlies in lexical sorting
     * order
     */
    while (current != nullptr)
    {
        /* if we are at the beginning of the list or it's the earliest
         * string in lexical order grab the previous node and the next
         * node at the current point so we can easily remove the current
         * pointer
         * later
         */
        if (pair.second == nullptr ||
        	(*current)->data < (*(pair.second))->data)
        {
            pair.first = prev;
            pair.second = current;
        }
        /* sed prev and current - please node that these are pointers
         * to unique_ptr<node> and so the setting of current is a little
         * more complicates
         */
        prev = current;

        current = (*current == nullptr || (*current)->next == nullptr)
            	  ? nullptr
            	  : &((*current)->next);
    }
    return pair;
}

/**
 * implementation of the sort algorithm
 **/
// Oisín Note: I don't think this class will work correctly after being sorted, 
// as the tail pointer will probably not point to the correct element.
void cpt323::list::custom_list::sort(void)
{
    /* empty list that we will insert all values into in sorted order. Ie,
     * this function implements an insertion sort
     */
    cpt323::list::custom_list sortedlist;
    /* pointer to the end of the new list (the sorted list) */
    nodeptr endptr = nullptr;
    /* keep iterating over the list until we have removed all nodes from the
     * list
     */
    while (!empty())
    {
        /* get the prev and current pointers to remove the element with
         * the smallest lexical value from the list
         */
        nodeptrpair min = find_min();
        /* remove from the list */
        std::unique_ptr<list_node> removed = std::move(*(min.second));
        /* if previous is NULL, we update the head pointer to point to
         * the
         * second element of the list (head becomes nullptr if there was
         * only one element left */
        if (!min.first)
        {
            if (removed)
            {
                if (removed->next)
                {
                    head = std::move(removed->next);
                }
                else
                {
                    head = nullptr;
                }
            }
        }
        else
        {
            /* if we are removing from elsewhere in the list (other
             * than the
             * head), set prev->next to current->next
             */
            (*min.first)->set_next(std::move(removed->next));
        }
        --num_elts;
        /* keep track track of the last element that has been inserted
         * into
         * the sorted list as the next element to be added will be added
         * to the end of the sorted list
         */
        if (!endptr)
        {
            sortedlist.head = std::move(removed);
            endptr = &sortedlist.head;
        }
        else
        {
            (*(endptr))->next = std::move(removed);
            endptr = &(*(endptr))->next;
        }
        ++sortedlist.num_elts;
    }
    assert(empty());
    /* all elements have be transferred to the sorted list at this point and
     * so we just move the head back to the original list */
    head = std::move(sortedlist.head);
    num_elts = sortedlist.num_elts;
}

/**
 * does this iterator point to the same spot as another iterator?
 **/
bool cpt323::list::custom_list::list_iterator::operator==(
    const cpt323::datastructure::datastructure::iterator& it)
{
    auto cast_iter = dynamic_cast<const cpt323::list::custom_list::list_iterator *>(&it);
    if(cast_iter == nullptr)
    {
        return false;
    }
    return cast_iter->inner == inner;
}

/**
 * does this iterator point to a different spot than another iterator?
 **/
bool cpt323::list::custom_list::list_iterator::operator!=(
    const cpt323::datastructure::datastructure::iterator& it)
{
    return !(*this == it);
}

void cpt323::list::custom_list::print(void)
{
    std::ostringstream oss;
    for (auto& word : *this)
    {
        oss << *word << "\n";
    }
    std::cout << oss.str();
}
