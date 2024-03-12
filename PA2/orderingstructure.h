/**
 * @file        orderingstructure.h
 * @description Definition of an abstract ordering structure class.
 *
 *              THIS FILE WILL NOT BE MODIFIED/SUBMITTED
 */
#ifndef _ORDERINGSTRUCTURE_H_
#define _ORDERINGSTRUCTURE_H_

/**
 * OrderingStructure: represents an interface for a structure that orders
 *   items placed into it. Your Stack and Queue classes will implement this
 *   interface.
 */
template <class T> class OrderingStructure {
    public:
        /**
         * Destructor for the OrderingStructure. Virtual so as to allow
         * derived classes to override if necessary.
         */
        virtual ~OrderingStructure() {
          // nothing
        }

        /**
         * Adds the given element to the ordering structure.
         * @param  item The item to be added.
         * @post item has been added to the ordering structure.
         */
        virtual void Add(const T& item) = 0;

        /**
         * Removes an element from the ordering structure. You may assume
         * that this function is only called when the ordering structure is
         * not empty.
         * @post the appropriate element is removed from the ordering structure.
         * @return an element from the ordering structure.
         */
        virtual T Remove() = 0;

        /**
         * Looks at the next element of the ordering structure, but does
         * not remove it.
         * @return the next element on the ordering structure.
         */
        virtual T Peek() = 0;

        /**
         * Determines if the ordering structure is empty.
         * @return true if there are no elements in the ordering structure,
         *         false otherwise.
         */
        virtual bool IsEmpty() const = 0;
};
#endif
