/**
 * @file        stack.h
 * @description Definition of the Stack class.
 *
 *              THIS FILE WILL NOT BE MODIFIED/SUBMITTED
 */

#ifndef _STACK_H_
#define _STACK_H_

#define DEFAULTCAPACITY 4 // Initial capacity of the array.
#define EXPANSIONFACTOR 2 // Factor to multiply or divide current size by when resizing.
#define SHRINKRATE 4      // When the size of the array is less than this fraction of capacity, the array should resize

#include "orderingstructure.h"

template <class T>
class Stack : public OrderingStructure<T> {
    public:
        /**
         * Default constructor
         */
        Stack();

        /**
         * Destructor
         */
        ~Stack();

        /**
         * Adds the parameter object to the top of the Stack
         * @param item the object to be added to the Stack
         * @post  the Stack contains newitem at the top, as its most recently added item.
         */
        void Push(const T& item);

        /**
         * Removes the object on top of the Stack, and returns it.
         * @post the most recently added item is removed from the collection.
         * @return the element that used to be at the top of the Stack.
         */
        T Pop();

        /**
         * Adds the given element to the ordering structure.
         * See OrderingStructure::Add()
         */
        void Add(const T& item);

        /**
         * Removes an element from the ordering structure. You may assume
         * that this function is only called when the ordering structure is
         * not empty.
         * See OrderingStructure::Remove()
         */
        T Remove();

        /**
         * Finds the object on top of the Stack, and returns it to the caller.
         * Unlike Pop(), this operation does not alter the Stack itself.
         * @return the element at the top of the Stack.
         */
        T Peek();

        /**
         * Determines if the Stack is empty.
         * @return true if the stack is empty,
         *         false otherwise.
         */
        bool IsEmpty() const;

        /**
         * Return the maximum number of items the stack can hold.
         *
         * Note: This is an implementation detail we would normally hide.
         * We include it here for testing purposes.
         */
        size_t Capacity() const;

        /**
         * Return the number of items on the stack.
         */
        size_t Size() const;

    private:
        /**
         * The maximum number of items the stack can store without a resize
         */
        size_t max_items;

        /**
         * The number of items currently in the stack
         */
        size_t num_items;

        /**
         * The dynamic array representing our Stack
         */
        T* items;

        /**
         * Resize the member variable 'items'.
         * The minimum size is the number of items in the Stack.
         * Don't forget to free up any memory that is no longer used.
         * @param n the capacity of the stack after resizing
         */
        void Resize(size_t n);
};

#include "stack.cpp" // needed for template instantiation

#endif
