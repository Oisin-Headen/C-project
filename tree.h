/******************************************************************************
 * Author Name: Paul Miller
 * Author ID: E70949
 * File Name: tree.h
 * All copyright in this material resides with RMIT University.
 *****************************************************************************/
/******************************************************************************
 * purpose of this file: define the specification of the custom tree for this
 * application.
 *****************************************************************************/
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include "iter_util.h"


#include "datastructure.h"

#pragma once

namespace cpt323::tree
{
    /* the node class */
    class tree_node
    {
        /* each node has pointers to left, right and a data element */
        std::unique_ptr<tree_node> left;
        std::unique_ptr<tree_node> right;
        std::string data;
        /* the tree class is a friend and so it can access any of the
         * internal data
         */
        friend class custom_tree;

    public:
        /* constructor : initialise the data and set the left and
         * right pointers to nullptr */
        tree_node(const std::string& _data)
            : left(nullptr), right(nullptr), data(_data)
        {
        }

        void add(const std::string&);

        /* setting the left and right pointers - we make this node
         * the owner of all the children of this node */
        void set_left(std::unique_ptr<tree_node>&& newleft)
        {
            left = std::move(newleft);
        }

        void set_right(std::unique_ptr<tree_node>&& newright)
        {
            right = std::move(newright);
        }
    };

    /**
     * our tree class
     **/
    class custom_tree: public cpt323::datastructure::datastructure
    {
        /* the root node is the owner of all child nodes */
        std::unique_ptr<tree_node> root;
        /* total nodes in the tree */
        std::size_t num_nodes;

    public:
        /* the iterator for our tree */
        class tree_iterator: public cpt323::datastructure::datastructure::iterator
        {
            /* the current node in our tree */
            tree_node* inner;
            /* a stack of nodes we are yet to visit for an
             * in-order iteration */
            std::stack<tree_node*> nodestack;

        public:
            /* functions implemented in the cpp file */
            tree_iterator(void);
            tree_iterator(tree_node*);
            const std::string& operator*(void) const override;
            std::unique_ptr<iterator> operator++(void) override;
            std::unique_ptr<iterator> operator++(int) override;
            void push_nodes(tree_node*);
            bool operator==(const iterator&) override;
            bool operator!=(const iterator&) override;
        };

    public:
        custom_tree(void);
        void add(const std::string&) override;
        std::unique_ptr<iterator> begin(void) override;
        std::unique_ptr<iterator> end(void) override;
        std::size_t size(void) override;

        /* empty sort function for the sake of simulation */
        void sort(void) override
        {
        }

        /* is the tree empty ? (no nodes) */
        bool empty(void) override
        {
            return root == nullptr;
        }

        /* for destruction there is no work to do as all objects have
         * their own destructors */
        virtual ~custom_tree(void)
        {
        }
    };
} // namespace cpt323::tree
