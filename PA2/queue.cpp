/**
 * @file        queue.cpp
 * @description Implementation of the Queue class.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * NOTE: This fuction should have O(1) behavior over n operations!
 *
 * @param item - object to be added to the Queue.
 */
template <class T>
void Queue<T>::Enqueue(T const& item)
{
	// complete your implementation below
	
}

/**
 * Removes the object at the front of the Queue, and returns it to
 * the caller. You may assume that this function is only called
 * when the Queue is non-empty.
 *
 * NOTE: This function should have O(1) behavior over n operations!
 *
 * @return the item that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::Dequeue()
{
	// complete your implementation below
  
	T item;      // REPLACE THESE LINES
	return item; // REPLACE THESE LINES
}

/**
 * Adds an element to the ordering structure.
 *
 * See OrderingStructure::Add()
 */
template <class T>
void Queue<T>::Add(const T& item)
{
	// complete your implementation below
	// Hint: this function should call a Queue
	//  function to add the element to the Queue.

	
}

/*
*  Removes an element from the ordering structure.
*
*  See OrderingStructure::Remove()
*/
template <class T>
T Queue<T>::Remove()
{
	// complete your implementation below
	// Hint: this function should call a Queue
	// function to remove an element from the Queue and return it. You will
	// need to replace the following lines.
  
	T item;      // REPLACE THESE LINES
	return item; // REPLACE THESE LINES
}

/*
*  Finds the object at the front of the Queue, and returns it to
*  the caller. Unlike Dequeue(), this operation does (conceptually!) not alter the
*  Queue; however, you may need to alter the internal representation of the Queue.
*  You may assume that this function is only called when the
*  Queue is non-empty.
*
*  NOTE: This function should have O(1) behavior over n operations!
*
*  @return the item at the front of the queue.
*/
template <class T>
T Queue<T>::Peek()
{
	// complete your implementation below
  
	T item;      // REPLACE THESE LINES
	return item; // REPLACE THESE LINES
}

/*
*  Determines if the Queue is empty.
*
*  @return true if the stack is empty,
*          false otherwise.
* 
*  NOTE: This function must always run in O(1) time!
*/
template <class T>
bool Queue<T>::IsEmpty() const
{
	// complete your implementation below
  
	return true; // REPLACE THIS STUB
}
