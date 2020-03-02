/******************************************************************************
 * Author Name: Paul Miller
 * Author ID: E70949
 * File Name: list.h
 * All copyright in this material resides with RMIT University.
 *****************************************************************************/
/******************************************************************************
 * Purpose of this file: to specify the public interface and internal structure
 * of the custom list class for this application
 *****************************************************************************/
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <sstream>


#include "datastructure.h"
#include "iter_util.h"

#pragma once

namespace cpt323::list
{
	/* the node struct for our list */
	class list_node
	{
		/* each pointer is "owned" by the previous pointer and head is
		 * "owned by the list
		 */
		std::unique_ptr<list_node> next;
		/* the data for this node */
		std::string data;
		friend class custom_list;

	public:
		/* create a new node that contains the string specified */
		list_node(const std::string& newstr)
		{
			data = newstr;
			next = nullptr;
		}

		/* sets the next unique_ptr */
		void set_next(std::unique_ptr<list_node>&& next);
		/* frees the node - it is sufficient for this function to be
		 * virtual as all elements of the struct are destructible by
		 * default
		 */
		virtual ~list_node()
		{
		}
	};

	/* these typedefs come in handy when finding the next element to remove
	 * from the list
	 */
	/* a nodeptr pair defines the previous and next pointers surrounding the
	 * element to remove */
	using nodeptr = std::unique_ptr<list_node>*;
	using nodeptrpair = std::pair<nodeptr, nodeptr>;
	
	
	/**
	 * The list class to represent a singly linked list
	 **/
	class custom_list: public cpt323::datastructure::datastructure
	{
		/* head owns all the other elements of the list because if head
		 * is deleted the rest of the list is deleted
		 */
		std::unique_ptr<list_node> head;
		list_node * tail;
		std::size_t num_elts;

		/**
		 * inner class iterator of the list - it's an inner class so it
		 * can have access to the private data of the list which it
		 * needs to do to keep track of the current element in an
		 * iteration
		 **/
		class list_iterator: public datastructure::datastructure::iterator
		{
			/* the node currently pointed to */
			list_node* inner;

		public:
			/**
			 * default constructor for the iterator - simply set the
			 * current pointer to NULL.
			 **/
			list_iterator() : inner(nullptr)
			{
			}
			/**
			 * the rest of these functions will be defined in the
			 * cpp file:
			 **/
			list_iterator(list_node*);
			const std::string& operator*(void) const override;
			std::unique_ptr<iterator> operator++(void) override;
			std::unique_ptr<iterator> operator++(int) override;
			bool operator==(const iterator&) override;
			bool operator!=(const iterator&) override;
		};

	public:
		/* public function / method members of the list */
		custom_list(void);
		void add(const std::string&) override;
		std::unique_ptr<iterator> begin(void) override;
		std::unique_ptr<iterator> end(void) override;
		std::size_t size(void) override;
		void sort(void) override;

		void print(void);
		nodeptrpair find_min(void);

		/**
		 * test that the list is empty
		 **/
		virtual bool empty(void) override
		{
			return size() == 0;
		}

		/**
		 * destructor for a list. Needs to be here and empty as the
		 *members of this
		 * class are all destructible
		 **/
		virtual ~custom_list(void)
		{
		}
	};
} // namespace cpt323::list
