#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

template<typename Data>
class BST {

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
   */
  BST() : root(nullptr), isize(0), maxHeight(0) {}


  /** Default destructor.
      Delete every node in this BST.
  */
  ~BST();

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return a pair where the first element is an iterator 
   *  pointing to either the newly inserted element or the element 
   *  that was already in the BST, and the second element is true if the 
   *  element was newly inserted or false if it was already in the BST.
   * 
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  
   */
  std::pair<iterator, bool> insert(const Data& item);


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const;

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const;
  
  /** Return the height of the BST.
      height of a tree starts with root at height 0
   */ 
  unsigned int height() const;


  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const;

  /** Return an iterator pointing to the first (smallest) item in the BST.
   */ 
  iterator begin() const;

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const;


private:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;
  
  /** Number of Data items stored in this BST. */
  unsigned int isize;

  unsigned int maxHeight;

  void heightTracker(const unsigned int h);

  /** Find the first element of the BST
   * Helper function for the begin method above.
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root);

  /** do a postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n);
 };


// ********** Function definitions ****************


/** Default destructor.
    Delete every node in this BST.
*/
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either the newly inserted
 *  element or the element that was already in the BST, and the second element is true if the 
 *  element was newly inserted or false if it was already in the BST.
 * 
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
   if (!root) //adds the root to the BST.
  {  
    root = new BSTNode<Data>(item); // create a new node and assign it to the root 
    isize++; // increment the size of BST. Height should remain zero. 
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(root), true);  // height should remain zero
  }

  BSTNode<Data>* curr = root;  //create pointer to the root
  bool added = false;  // element added or not 
  unsigned int tempHeight = 0; // keeps track of height of tree during insert operation 

  while (true) // while curr node exists 
  {
      if (curr->data < item)  // that means look at right child
      {
        if (!curr->right) // that means the curr->right does not exist
        {
            curr->right = new BSTNode<Data>(item);
            curr->right->parent = curr;
            isize++;
            tempHeight++;
            added = true;
            heightTracker(tempHeight);
           return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr->right), added); 
        }

        else // there exists a right child
        {
          curr = curr->right;
          tempHeight++;
        }
      }

      else if (item < curr->data)  // that means look at left child
      {
        if (!curr->left) // that means the left child does not exist
        {
            curr->left = new BSTNode<Data>(item);
            curr->left->parent = curr;
            isize++;
            tempHeight++;
            added = true;
            heightTracker(tempHeight);
            return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr->left), added);
        }

        else // there exists a left child
        {
            curr = curr->left; 
            tempHeight++;
        }
      }

      else  // that means the value already exists in the loop 
      {
        added = false;
        return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr), false);
      }
  }

  heightTracker(tempHeight);
  return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(0), false);



}

/** Keeps track of height.
 */ 
template <typename Data>
void BST<Data>::heightTracker(const unsigned int tempHeight) 
{
    if (maxHeight < tempHeight)
      maxHeight = tempHeight;
}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{

  BSTNode<Data>* curr = root;  
  while (curr)  // while curr Node exists  
  {
    if (curr->data < item) { // right child 
      curr = curr->right;
    }
    else if (item < curr->data) { //left child
      curr = curr->left;
    }
    else {
      return BSTIterator<Data>(curr); // returns true when found 
    }
  }

  return end(); // returns this if not found

}

  
/** Return the number of items currently in the BST.
 */ 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

/** Return the height of the BST.
 */
template <typename Data> 
unsigned int BST<Data>::height() const
{
  return maxHeight;
}


/** Return true if the BST is empty, else false.
 */ 
template <typename Data>
bool BST<Data>::empty() const
{
    return (isize == 0) ? true : false; 
}

/** Return an iterator pointing to the first (smallest) item in the BST.
 */ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */ 
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root) 
{
  BSTNode<Data>* curr = root;

  if (!curr)
  {
  	// curr is simply null, so nothing to be done 
  }

  else if (!curr->left)
  {
  	// curr is root if no left child
  }

  else
  	while (curr->left)
  		curr = curr->left;

  return curr;

}

/** do a postorder traversal, deleting nodes
 */
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
   if (n != NULL)  //only execute when N exists 
  { 
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
  }
}



#endif //BST_HPP
