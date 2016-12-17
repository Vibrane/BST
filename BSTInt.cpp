#include "BSTInt.h"

/* Function definitions for a int-based BST class */


/** Default destructor.
    Delete every node in this BST.
*/
BSTInt::~BSTInt() {
  deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  For the reasoning
 *  behind this, see the assignment writeup.
 */

bool BSTInt::insert(int item)
{
  if (!root) //adds the root to the BST.
  {  
    root = new BSTNodeInt(item); // create a new node and assign it to the root 
    isize++; // increment the size of BST
    return true;  // height should remain zero
  }

  BSTNodeInt* curr = root;  //create pointer to the root
  bool added = false;  // element added or not 
  unsigned int tempHeight = 0; // keeps track of height of tree during insert operation 

  while (true) // while curr node exists 
  {
      if (curr->data < item)  // that means look at right child
      {
        if (!curr->right) // that means the curr->right does not exist
        {
            curr->right = new BSTNodeInt(item);
            curr->right->parent = curr;
            isize++;
            tempHeight++;
            added = true;
            break;  //successfully added 
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
            curr->left = new BSTNodeInt(item);
            curr->left->parent = curr;
            isize++;
            tempHeight++;
            added = true;
            break; // successfully added 
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
        break;
      }
  }

  if (treeHeight < tempHeight)
      treeHeight = tempHeight;

  return added;

  //starter code insert that has to be debugged
  // while (curr->left && curr->right) { 
  //   if (item < curr->data) {
  //     curr = curr->left;
  //   }
  //   else if (curr->data < item) {
  //     curr = curr->right;
  //   }
  //   else {
  //     return false;
  //   }
  // }
  // 
  // 5, 1, 3 
  // // Ready to insert
  // BSTNodeInt* newNode = new BSTNodeInt(item);
  // if (item < curr->data) {
  //   curr->left = newNode;
  //   newNode->parent = curr;
  // }
  // else {
  //   curr->right = newNode;
  //   newNode->parent = curr;
  // }

  // ++isize;
  // return true;
  
}


/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
bool BSTInt::find(int item) const
{
  BSTNodeInt* curr = root;

  while (curr)  // while curr Node exists  
  {
    if (curr->data < item) { // right child 
      curr = curr->right;
    }
    else if (item < curr->data) { //left child
      curr = curr->left;
    }
    else {
      return true; // returns true when found 
    }
  }
  return false; 
}

  
/** Return the number of items currently in the BST.
 */
unsigned int BSTInt::size() const 
{
  return isize;
}

  
/** Return the height of the BST.
    Height of tree with just root node is 0
 */
unsigned int BSTInt::height() const
{
  return treeHeight;
}


/** Return true if the BST is empty, else false. 
 */
bool BSTInt::empty() const 
{
  return (isize == 0) ? true : false;  
}

/** do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 */
void BSTInt::deleteAll(BSTNodeInt* n)
{
  if (n != NULL)  //only execute when N exists 
  {
    deleteAll(n->left);
    deleteAll(n->right);
    delete n;
  }
}
